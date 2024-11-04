void setup()
{
    pinMode(13, OUTPUT);
}

void loop()
{
    digitalWrite(13, HIGH);
    delay(500); // Wait for 500 milliseconds
    digitalWrite(13, LOW);
    delay(500); // Wait for 500 milliseconds
}
