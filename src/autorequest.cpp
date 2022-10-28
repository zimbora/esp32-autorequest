
#include "autorequest.hpp"

#ifndef UNITTEST
//DynamicJsonDocument doc_ar(1024);
StaticJsonDocument<1024> doc_ar; // json doc to store autorequest - Use 100 Bytes for each one
#else
nlohmann::json doc_ar;
#endif

bool AUTOREQUEST::check(String ref,bool(*execute)(String ref)){
  if(check(ref))
    return execute(ref);
}

bool AUTOREQUEST::check(String ref){

  if(year() < 2018) return false;  // clock isn't sync(ed)

  uint32_t timeout = doc_ar[ref]["timeout"];
  int16_t period = doc_ar[ref]["period"];

  #ifdef DEBUG_AUTOREQUEST
  log(String(ref)+": "+String(timeout)+"("+String(period)+")");
  #endif
  uint32_t now_ = now();
  if(timeout <= now_ || (timeout - period > now_) ){
    uint32_t timeout = get_aligned_hour(period);
    timeout += period;
    doc_ar[ref]["timeout"] = timeout;

    #ifdef DEBUG_AUTOREQUEST
    log("timeout: "+String(timeout));
    log("period: "+String(period));
    log("timestamp: "+String(now_) );
    log("align to: "+String(timeout));
    log("new timeout: "+String(timeout));
    #endif

    return true;
  }

  return false;
}

bool AUTOREQUEST::add(String ref, uint32_t period){

  uint32_t timeout = get_aligned_hour(period)+period;
  doc_ar[ref]["period"] = period;
  doc_ar[ref]["timeout"] = timeout;

  return doc_ar.containsKey(ref);
}

uint32_t AUTOREQUEST::get_aligned_hour(uint32_t period){

  time_t unix_time = now();

  if(use_local_time){
		unix_time += time_offset;
	}

  unix_time -= (unix_time % period);    // minute align
  return unix_time;
}

void AUTOREQUEST::log(String text){
  #ifndef UNITTEST
    serial->println("[autorequest] "+text);
  #else
    std::cout << "[autorequest] " << text << std::endl;
  #endif
}

#ifdef UNITTEST
uint32_t AUTOREQUEST::now(){
  return getTimestamp();
};
#endif
