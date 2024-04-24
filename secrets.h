
#include <pgmspace.h>
 
#define SECRET
#define My_THING_NAME "ESP32_DHT11"                         
 
const char NETWORK_USER [] = "Wokwi-GUEST";               
const char NETWORK_SECRET [] = "";           
const char AWS_CORE_THING[] = "a1v3e7acmb8s7z-ats.iot.us-east-1.amazonaws.com";       

static const char AWS_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";
 

static const char AWS_THING_CERTIFICATE[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAJYbq8KfWJSfVPTQbp8qC58EcvYIMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yNDAxMjUwNjEx
NDJaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDcSCxiGTGxVjs3ZwiC
LSK6mJlA4h9yxVyBFUA95DIPb5yQZwn9pAeC/057RZ7hbBlVu18/XKwqk8HniwNS
jQMhPfa2zgiKlc5BMR+Rdy4acR5roszuEYuIc10qa7T1AQGzPLJxw/BgGZ/GTkRT
flojLb7YFZsIYnN1Hc7Rk4lpfA/7TSpaSebG+CCWG6IHMUePJSo8gP5MDt2xw4Tm
/NA65/3VsU19HqOWTjan0hlrDcbwedvgbYhtNUMiDfW0Bn9Hg+dfb6daXg2lridH
UAXIo0xJaSj5oQaUR38cW9E+hMmnUuE/tZWB++cUU5lWAEhQe1NnL5WcR5wTo2Fb
+K4dAgMBAAGjYDBeMB8GA1UdIwQYMBaAFAaTjbr4s9MoztuvuHi5tVTtOXisMB0G
A1UdDgQWBBQGomGCRJVg9+JqlUynd6iljAkeGzAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAdV1qEO4/hoondqmt0WgZ3bby
bQ7Mox+AY6/gf/HL2xxn7QCrUvOMZc6xuLti9Tdj4w8ilBsLJihiHdPGgJpdizNR
9MnI68d+pygvoTHJ/Wg0LAnGLInHQIqUGKYxppl92fOcUUEIjqY+rmE3YeXNBcbv
wbIA0Kkk7cqw7UY87+NKdE0VxBFlGzgzpHTkWajlUH7RtDYJVGE7nYx+pMt5YoOm
QyxDxN/IFxK6tVlKVUIHGGeHNsGGwKLOegqf8jEpXWy/gNUx2Acy1WBsWWdtWQGl
BA2y7vHXSjwKUohyetpDvHEDZ2J7PQS+JXNmWJwpVTuv8FVPByf462tDuIrCXg==
-----END CERTIFICATE-----
)KEY";
 

static const char AWS_SECRET_KEY[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEA3EgsYhkxsVY7N2cIgi0iupiZQOIfcsVcgRVAPeQyD2+ckGcJ
/aQHgv9Oe0We4WwZVbtfP1ysKpPB54sDUo0DIT32ts4IipXOQTEfkXcuGnEea6LM
7hGLiHNdKmu09QEBszyyccPwYBmfxk5EU35aIy2+2BWbCGJzdR3O0ZOJaXwP+00q
WknmxvgglhuiBzFHjyUqPID+TA7dscOE5vzQOuf91bFNfR6jlk42p9IZaw3G8Hnb
4G2IbTVDIg31tAZ/R4PnX2+nWl4Npa4nR1AFyKNMSWko+aEGlEd/HFvRPoTJp1Lh
P7WVgfvnFFOZVgBIUHtTZy+VnEecE6NhW/iuHQIDAQABAoIBABcBAoGMGABo/O4g
OGc/x2ytGvQHqTkXGz3vtjHAbunlwffiisyOIKqxdsSw1JK98zdcxemcB+66V3mS
rtokF7uU+PrGMWYnls6ADsfmJk5kmcSrz7Lc6jFpusT/UnpzjHXnVMtEpwmiI2lW
KxR9EXSzBkcSmooZne0RG9QPED6PoIWq1XeyqbokKg6n6Zv+yZgzy/vsqmuA3Fvy
4F8eQICRPvmSspaEakudLBR6X9iLN2glnT7vpjp5AXCoF992mN+GGgTheobQ/3Oc
Fku11pMivr8x2OkgkGs/8J8V9aK0bJI2P6uQsc/ddXgn+QVIYK0g4sUDMtv8nCgf
npPjapECgYEA+FdQ9wEn61AubnBLIGx9mfpqZjLNJPPp9OhPGVoF11YUt46ci/8s
zpC76jsVIhuBwNrdyIA4yaLPucWQ6+5ghhgolti5Kl55eCheWb4VUUDEBTB2PlVf
CSXmtFv+UoA8EHeeIQ6nP8O9G/gqKliK6+QafhP81N8TXCWJPKMKk/cCgYEA4xNT
nG+4cmHFMyoUbILlvccZd+RF8K3A995H0kPaHBlGzGGmoSDrEZ3nl+vSzGkEeESz
qd9/z55Jj5VJZkD+FkgVFcN6NqbG39P1grvLwFB2n3NMFhHfyAYUV0f5X0xYnDYI
xFAp0ELWAmi2oYPD1ptM8Ak2WTuA2Y//2+A0oYsCgYB+7GmGBII5gx5n9V6AMNK0
2sZ8eyRb6Ym+UOj0ZQ0tNGKcOfgKmR12aYSRPyca6oITZgkKC3Z6n4qZQL9Dxe5x
OnGsPxHL9MMSRVeLeFn+0CIfINieHRXYYBWcQpQl6EJKjEg2Tv3t2gWSAPDT+bLu
wwNDQsXqqiSD6O9OHWovmwKBgCXxicwfIvwB+Fi3VFhZexg+F7Rf8YvpDNCeVPP+
oIiHdLwcKSLNhFoaP6O0JTJA7h1GpZriHNJNic8zS+OJQqvoeZV8Z4SQU7T9Dw48
YSyOhXPZaUJa1EDxOx7miPXypO/dW5OqLYJ+WJJoevP8N5I5ux50+57ngX1ZQZC1
IzZHAoGBAKbWwWC+tiKXdgzliVfRgo7/PufA2YrnposNAs/c+OUhrIIUGw7nbnmm
LtXvAgQuYQvIZAEz3gn38oe1Am3QcBd65qEgnw2YcRCx1ezXxOAAliLi5ob1ozhn
YXyzHQ/JVTOtli/YdflfAM+BikZjGWoMcZS9VWUM9uB/D1Nx+dGf
-----END RSA PRIVATE KEY-----
)KEY";


