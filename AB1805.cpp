#include "AB1805.h"

AB1805::AB1805() {}

// Use these methods with I2c library instead of Wire
/*
void AB1805::begin()
{
	I2c.begin();
}

uint8_t AB1805::read_rtc_register(const uint8_t rtc_register) {
    
	I2c.write(AM1805, rtc_register);
    I2c.read(AM1805, (uint8_t) 1);
    
	return I2c.receive();
}

uint8_t AB1805::write_rtc_register(const uint8_t rtc_register, const uint8_t data) {
    
	I2c.write(AM1805, rtc_register, data);  
    
	return true;
}
*/

void AB1805::begin()
{
	Wire.begin();
}


uint8_t AB1805::read_rtc_register(const uint8_t rtc_register) {
	uint8_t data;									// `data` will store the register data	 
	Wire.beginTransmission(AM1805);					// Initialize the Tx buffer
	Wire.write(rtc_register);	              		// Put slave register address in Tx buffer
	Wire.endTransmission(false);             		// Send the Tx buffer, but send a restart to keep connection alive
	Wire.requestFrom(AM1805, (uint8_t) 1);  	// Read one byte from slave register address 
	data = Wire.read();                      		// Fill Rx buffer with result
	return data;                             		// Return data read from slave register
}


uint8_t AB1805::write_rtc_register(const uint8_t rtc_register, const uint8_t data)
{
	Wire.beginTransmission(AM1805);  	// Initialize the Tx buffer
	Wire.write(rtc_register);    		// Put slave register address in Tx buffer
	Wire.write(data);					// Put data in Tx buffer
	Wire.endTransmission();				// Send the Tx buffer
	return true;
}

      

uint8_t AB1805::get_rtc_data(const uint8_t rtc_register, const uint8_t register_mask) {
    return (read_rtc_register(rtc_register) & register_mask);
}

uint8_t AB1805::get_second(void) {
    return get_rtc_data(SECOND_REGISTER, SECOND_MASK);
}

uint8_t AB1805::get_minute(void) {
    return get_rtc_data(MINUTE_REGISTER, MINUTE_MASK);
}

uint8_t AB1805::get_hour(void) {
    return get_rtc_data(HOUR_REGISTER, HOUR_24_MASK);
}

uint8_t AB1805::get_day(void) {
    return get_rtc_data(DAY_REGISTER, DAY_MASK);
}

uint8_t AB1805::get_date(void) {
    return get_rtc_data(DATE_REGISTER, DATE_MASK);
}

uint8_t AB1805::get_month(void) {
    return get_rtc_data(MONTH_REGISTER, MONTH_MASK);
}

uint8_t AB1805::get_year(void) {
    return get_rtc_data(YEAR_REGISTER, YEAR_MASK);
}

void AB1805::get_datetime(void)
{
  //rtc_check_valid();
  _seconds = get_second();
  _minutes = get_minute();
  _hour = get_hour();
  _day = get_day();
  _date = get_date();
  _month = get_month();
  _year = get_year();
}

uint8_t AB1805::get_seconds_alarm(void){
    _alarm_seconds = get_rtc_data(SECOND_ALARM_REGISTER, SECOND_ALARM_MASK);
    return _alarm_seconds;
}

uint8_t AB1805::get_minutes_alarm(void) {
    _alarm_minutes = get_rtc_data(MINUTE_ALARM_REGISTER, MINUTE_ALARM_MASK);
    return _alarm_minutes;
}

uint8_t AB1805::get_hour_alarm(void) {
    _alarm_hour = get_rtc_data(HOUR_ALARM_REGISTER, HOUR_24_ALARM_MASK);
    return _alarm_hour;
}

uint8_t AB1805::get_day_alarm(void) {
    _alarm_day = get_rtc_data(DAY_ALARM_REGISTER, WEEKDAY_ALARM_MASK);
    return _alarm_day;
}

uint8_t AB1805::get_date_alarm(void) {
    _alarm_date = get_rtc_data(DATE_ALARM_REGISTER, DATE_ALARM_MASK);
    return _alarm_date;
}

uint8_t AB1805::get_month_alarm(void) {
    _alarm_month = get_rtc_data(MONTH_ALARM_REGISTER, MONTH_ALARM_MASK);
    return _alarm_month;
}

/*
uint8_t AB1805::get_year_alarm(void) {
    _alarm_year = get_rtc_data(YEAR_ALARM_REGISTER, YEAR_ALARM_MASK);
    return _alarm_year;
}*/

void AB1805::set_second(const uint8_t value) {
    _seconds = value % MAX_SECOND;
    write_rtc_register(SECOND_REGISTER, _seconds);
}

void AB1805::set_minute(const uint8_t value) {
    _minutes = value % MAX_MINUTE;
    write_rtc_register(MINUTE_REGISTER, _minutes);
}

void AB1805::set_hour(const uint8_t value) {
    _hour = value % MAX_HOURS;
    write_rtc_register(HOUR_REGISTER, _hour);
}

void AB1805::set_day(const uint8_t value) {
    _day = value % MAX_DAY;
    write_rtc_register(DAY_REGISTER, _day);
}

void AB1805::set_date(const uint8_t value) {
    _date = value % MAX_DATE;
    write_rtc_register(DATE_REGISTER, _date);
}

void AB1805::set_month(const uint8_t value) {
    _month = value % MAX_MONTH;
    write_rtc_register(MONTH_REGISTER, _month);
}

void AB1805::set_year(const uint8_t value) {
    _year = value % MAX_YEAR;
    write_rtc_register(YEAR_REGISTER, value);
}

void AB1805::set_datetime(uint8_t year, uint8_t month, uint8_t date, 
  uint8_t day, uint8_t hour, uint8_t minutes, uint8_t seconds) {
    set_year(year);
    set_month(month);
    set_date(date);
    set_day(day);
    set_hour(hour);
    set_minute(minutes);
    set_second(seconds);
}

bool AB1805::set_seconds_alarm(uint8_t value) {
    _alarm_seconds = value % MAX_SECOND;
    return (value == _alarm_seconds);
}

bool AB1805::set_minutes_alarm(uint8_t value) {
    _alarm_minutes = value % MAX_MINUTE;
    return (value == _alarm_minutes);
}

bool AB1805::set_hour_alarm(uint8_t value) {
    _alarm_hour = value % MAX_HOURS;
    return (value == _alarm_hour);
}

bool AB1805::set_day_alarm(uint8_t value) {
    _alarm_day = value % MAX_DAY;
    return (value == _alarm_day);
}

bool AB1805::set_date_alarm(uint8_t value) {
    _alarm_date = value % MAX_DATE;
    return (value == _alarm_date);
}

bool AB1805::set_month_alarm(uint8_t value) {
    _alarm_month = value % MAX_MONTH;
    return (value == _alarm_month);
}

bool AB1805::set_year_alarm(uint8_t value) {
    _alarm_year = value % MAX_YEAR;
    return (value == _alarm_year);
}


String AB1805::get_date_string(void){
  
  String date_string;
  
  _date = get_date();
  date_string += ((_date & 0xF0) >> 4);
  date_string += (_date & 0x0F);
    
  date_string += '/';
  
  _month = get_month();
  date_string += ((_month & 0xF0) >> 4);
  date_string += (_month & 0x0F);
  
  date_string += '/';
  
  _year = get_year();
  date_string += ((_year & 0xF0) >> 4);
  date_string += (_year & 0x0F);
  
  date_string += ' ';
  
  _hour = get_hour();
  date_string += ((_hour & 0xF0) >> 4);
  date_string += (_hour & 0x0F);
  
  date_string += ':';
  
  _minutes = get_minute();
  date_string += ((_minutes & 0xF0) >> 4);
  date_string += (_minutes & 0x0F);
  
  date_string += ':';
  
  _seconds = get_second();
  date_string += ((_seconds & 0xF0) >> 4);
  date_string += (_seconds & 0x0F);
  
  
  return date_string;
  

}