unsigned int count, toggle;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  while (!Serial){;}
  Serial.println("hello world!");
  count=toggle=0;
  digitalWrite(13,toggle);
}

void loop() {
  Serial.println(++count);
  toggle=toggle_state(toggle);
  digitalWrite(13,toggle);
  delay(1000);
}

int toggle_state(int toggle){
  if (toggle==0)
    ++toggle;
  else
    toggle=0;
  return toggle;
}
