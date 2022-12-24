#include "esp_camera.h"

#define CAMERA_MODEL_AI_THINKER

#include "camera_pins.h"

// Replace with your WiFi network name and password
const char *ssid = "your-ssid";
const char *password = "your-password";

// This function will be called when a client connects to the server
void onConnect(WiFiClient *client)
{
  Serial.println("New client connected");
  // Send the video stream to the client
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb)
  {
    Serial.println("Failed to get frame buffer");
    return;
  }

  // Send the HTTP header
  client->println("HTTP/1.1 200 OK");
  client->println("Content-Type: text/html");
  client->println("Connection: close");
  client->println();

  // Send the video stream
  client->write((uint8_t *)fb->buf, fb->len);

  // Release the frame buffer
  esp_camera_fb_return(fb);
  // Disconnect the client
  client->stop();
}

void setup()
{
  Serial.begin(115200);

  // Initialize the camera
  esp_err_t err = esp_camera_init(&camera_config);
  if (err != ESP_OK)
  {
    Serial.println("Failed to initialize camera");
    return;
  }

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected to WiFi. IP address: ");
  Serial.println(WiFi.localIP());

  // Start the server
  WiFiServer server(80);
  server.begin();
  Serial.println("Server started");
}

void loop()
{
  // Check for new clients
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }
  // Call the onConnect function when a client connects
}