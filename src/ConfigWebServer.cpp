#include "ConfigServer.h"

#ifdef NATIVE_SIM
void ConfigServer::begin() {}
void ConfigServer::loop() {}

#else
#include "BoardConfig.h"
#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
static WebServer server(80);
static void handleRoot() {
    File f = LittleFS.open("/config.json", "r");
    String json = f ? f.readString() : "{}";
    if (f) f.close();

    String html = R"HTML(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Config</title>
    <style>
        body { font-family: monospace; max-width: 800px; margin: 20px auto; }
        textarea { width: 100%; height: 400px; font-family: monospace; }
        button { padding: 10px 20px; font-size: 16px; cursor: pointer; }
        #status { margin-top: 10px; font-weight: bold; }
    </style>
</head>
<body>
    <h2>Yougille Config</h2>
    <textarea id="cfg">)HTML" + json + R"HTML(</textarea><br><br>
    <button onclick="saveConfig()">Save &amp; Reboot</button>
    <div id="status"></div>
    <p>IP: )HTML" + WiFi.localIP().toString() + R"HTML( | AP: )HTML" + WiFi.softAPIP().toString() + R"HTML(</p>
    <script>
        async function saveConfig() {
            const cfg = document.getElementById('cfg').value;
            const status = document.getElementById('status');
            status.textContent = 'Saving...';
            status.style.color = 'blue';
            
            try {
                const resp = await fetch('/save', {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: cfg
                });
                const text = await resp.text();
                if (resp.ok) {
                    status.textContent = text;
                    status.style.color = 'green';
                } else {
                    status.textContent = 'Error: ' + text;
                    status.style.color = 'red';
                }
            } catch (e) {
                status.textContent = 'Network error: ' + e.message;
                status.style.color = 'red';
            }
        }
    </script>
</body>
</html>
)HTML";
    server.send(200, "text/html", html);
}

static void handleSave() {
    // Читаем raw body напрямую, минуя парсинг form-полей
    String cfg = "";
    if (server.hasArg("plain")) {
        cfg = server.arg("plain");
    } else {
        // Фолбэк: читаем через stream
        WiFiClient client = server.client();
        while (client.available()) {
            cfg += (char)client.read();
        }
    }

    // Отладочный вывод в Serial, чтобы видеть, что пришло
    Serial.println("[Config] Received JSON:");
    Serial.println(cfg);

    // Валидируем JSON ДО записи
    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, cfg);
    if (err) {
        String errMsg = String("JSON error: ") + err.c_str();
        Serial.println("[Config] " + errMsg);
        server.send(400, "text/plain", errMsg);
        return;
    }

    File f = LittleFS.open("/config.json", "w");
    if (!f) {
        server.send(500, "text/plain", "fs error");
        return;
    }
    f.print(cfg);
    f.close();

    Serial.println("[Config] Saved successfully, rebooting...");
    server.send(200, "text/plain", "Saved. Rebooting...");
    delay(500);
    ESP.restart();
}

void ConfigServer::begin() {
    if (strlen(g_board.wifiSsid) > 0) {
        WiFi.mode(WIFI_STA);
        WiFi.begin(g_board.wifiSsid, g_board.wifiPass);
        int tries = 0;
        while (WiFi.status() != WL_CONNECTED && tries < 14) {
            delay(500);
            tries++;
        }
    }
    if (WiFi.status() != WL_CONNECTED) {
        WiFi.mode(WIFI_AP);
        WiFi.softAP("Yougille-Config", "12345678");
        Serial.print("[Config] AP raised, ip: ");
        Serial.println(WiFi.softAPIP());
    } else {
        Serial.print("[Config] STA connected, ip: ");
        Serial.println(WiFi.localIP());
    }

    server.on("/", handleRoot);
    server.on("/save", handleSave);
    server.begin();
}

void ConfigServer::loop() {
    server.handleClient();
}
#endif