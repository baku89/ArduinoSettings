#include <SD.h>
#include <ctype.h>

// default settings
#define DEFAULT_INT_VALUE   	0
#define DEFAULT_BOOL_VALUE		false
#define DEFAULT_STRING_VALUE	"default"

// settings
struct parameters {
  int 		intValue;
  bool 		boolValue;
  String 	stringValue;
} settings;

const int chipSelect = 8;

void setup()
{
	Serial.begin(9600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for Leonardo only
	}
	Serial.println("Starting...");
	pinMode(10, OUTPUT);

	if (!SD.begin(chipSelect)) {
		Serial.println("initialization failed!");
		return;
	}

	getSettings();

	Serial.println("----------");
	Serial.print("intValue: ");
	Serial.println(settings.intValue);
	Serial.print("boolValue: ");
	if(settings.boolValue) { Serial.println("YES"); } else { Serial.println("NO"); }
	Serial.print("stringValue: ");
	Serial.println(settings.stringValue);

}

void loop()
{
	;
}