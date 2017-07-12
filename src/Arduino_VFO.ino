void setup(){
  void setup_ad9850();
}

void loop(){
  VFO_Step_Down();
  VFO_Step_Up();
  VFO_setfreq_up();
  VFO_setfreq_down();
  VFO_band_up();
  VFO_band_down();
}
