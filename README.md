# esp32-autorequest

## Description
package to sync tasks with clock and calculate timestamp of next execution

## Implementation
Autorequests are stored in a JsonDocument with the following structure
```
  doc_alarm = {[
    ref : {
       "period" : period,
       "timeout" : timeout
     }]
  }
```
## Public Methods
[bool add(String ref, uint32_t period)](#Add-object-1)

[bool check(String ref)](#Check-Autorequest-1)

[bool check(String ref, bool(*callback)(String))](#Check-Autorequest-2)

[void list()](#List)

[JsonObject get(String ref)](#Get)

## Examples
  Run programs inside examples folder to check how it works
### demo
  Add autorequests and then check it forever
### demo_callback
  Add autorequests and then check it forever. If autorequest timed out registered callback is called
### test_limits
  Check how many autorequests can be handled with actual parameters

## Unit Test with clang
  >> chmod u+x make.sh

  >> ./make.sh

  If needed uncomment DEBUG FLAGS in Makefile

## TODO
  ..

## Public Methods - Extension

### Add object 1
return true if has succeed
```
bool AUTOREQUEST::add(String ref, uint32_t period)
```
#### Example
```
  if(!Ar.add("sensor2",300)){
    Serial.println("!! Error adding sensor2 autorequest");
  }
```

### Check Autorequest 1
return true if it is time to execute autorequest
```
bool AUTOREQUEST::check(String ref)
```
#### Example
```
  String ref = "sensor1"
  Ar.check(ref);
```

### Check Autorequest 2
return true if is in autorequest

call callback function if autorequest goes out of the range limit or returns to the range limit
```
bool AUTOREQUEST::check(String ref, bool(*callback)(String))
```
#### Example
```
bool (*callback)(String);
bool calledInAutorequest(String ref){
  Serial.println("autorequest was changed");
  return true;
}

callback = &calledInAutorequest;
Ar.check(ref,callback);
```

### List

```
void AUTOREQUEST::list()
```
#### Example
```
  Ar.list();
```

### Get

```
JsonObject AUTOREQUEST::get(String ref)
```
#### Example
```
  JsonObject object = Ar.get("sensor1");
```
