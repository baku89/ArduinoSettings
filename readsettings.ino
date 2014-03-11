File    confFile;
char    confChar;

boolean getSettings()
{
 // Open the settings file for reading:
  String  description = "";

  confFile = SD.open("SETTINGS.TXT");
  if (!confFile) {
    return false;
  }

  // read from the file until there's nothing else in it:
  while (confFile.available()) {
    confChar = confFile.read();

    if (confChar == '#')           { // Comment - ignore this line
      skipLine();

    } else if (isalnum(confChar))  { // Add a confChar to th e description
      description.concat(confChar);

    } else if (confChar =='=')     { // start checking the value for possible results

      // First going to trim out all trailing white spaces
      do {
        confChar = confFile.read();
      } while(confChar == ' ');

      // Property list
      if (description == "intValue") {
        settings.intValue = getIntSetting(DEFAULT_INT_VALUE);

      } else if (description == "boolValue") {
        settings.boolValue = getBoolSetting(DEFAULT_BOOL_VALUE);

      } else if (description == "stringValue") {
        settings.stringValue = getStringSetting(DEFAULT_STRING_VALUE);

      } else { // Unknown parameter - ignore this line
        skipLine();
      }

      description = "";

    } else {
      // Ignore this confChar (could be space, tab, newline, carriage return or something else)
    }
  }
  // close the file:
  confFile.close();

  return true;
}

void skipLine()
{
  do {
    confChar = confFile.read();
  } while (confChar != '\n');
}

int getIntSetting(int defaultValue)
{
  String  value = "";
  boolean valid = true;

  while (confChar != '\n') {
    if (isdigit(confChar) || confChar == '-') {
      value.concat(confChar);
    } else if (confChar != '\n') { // Use of invalid values
      valid = false;
    }
    confChar = confFile.read();            
  }
  
  if (valid) { 
    // Convert string to integer
    char charBuf[value.length()+1];
    value.toCharArray(charBuf,value.length()+1);
    return atoi(charBuf);
  } else {
    // revert to default value for invalid entry in settings
    return defaultValue;
  }
}

bool getBoolSetting(bool defaultValue)
{
  if (confChar == '1') {
    return true;
  } else if (confChar == '0') {
    return false;
  } else {
    return defaultValue;
  }
}

String getStringSetting(String defaultValue)
{
  String value = "";
  do {
    value.concat(confChar);
    confChar = confFile.read();
  } while(confChar != '\n');
  
  if (value != "") {
    return value;
  } else {
    return defaultValue;
  }

}