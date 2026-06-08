#include <WiFi.h>
#include <time.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// For hotspot/wifi:
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// Pakistan time = UTC + 5
const long gmtOffset = 5 * 3600;
const int daylightOffset = 0;

struct Period {
  int day;          // Mon = 1, Tues = 2, ... etc
  int startMin;     //in miins
  int endMin;       
  String subject;
  String teacher;
  String section;
};

Period timetable[] = {

  {1,  480,  660, "ISL",   "Mr Kamran",   "4th D"},
  {1,  660,  720, "DAA",   "Dr Maimoona", "4th D"},
  {1,  780,  960, "ADMSL", "Mr Waleed",   "4th D"},
  {1,  960, 1140, "DSL",   "Dr Maimoona", "2nd D"},

  {2,  480,  660, "DSL",   "Ms Hafsa",    "2nd B"},
  {2,  780,  960, "OOPL",  "Mr Muzaffar", "2nd D"},
  {2,  960, 1140, "PFL",   "Mr Laeeq",    "1st A"},

  {3,  480,  540, "ToA",   "Dr Tauqir",   "4th B"},
  {3,  540,  720, "COALL", "Sir Tehseen", "4th B"},
  {3,  780,  960, "DSL",   "Mr Nazeef",   "2nd E"},

  {4,  480,  660, "ADMSL", "Mr Waleed",   "4th B"},
  {4,  660,  720, "DAA",   "Dr Amna",     "4th B"},
  {4,  780,  960, "ISL",   "Mr Kamran",   "4th B"},
  {4,  960, 1140, "OOPL",  "Ms Nimra",    "2nd D"},

  {5,  480,  660, "OOPL",  "Ms Nimra",    "2nd E"}
};

int totalPeriods = sizeof(timetable) / sizeof(timetable[0]);

void setup() {
  Serial.begin(115200);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Lab1 Indicator");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  delay(1500);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connecting WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected");
  delay(1000);

  configTime(gmtOffset, daylightOffset, "pool.ntp.org");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Syncing Time");

  struct tm timeinfo;
  while (!getLocalTime(&timeinfo)) {
    delay(500);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time Synced");
  delay(1000);
}

void loop() {
  struct tm timeinfo;

  if (!getLocalTime(&timeinfo)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Time Error");
    delay(1000);
    return;
  }

  int today = timeinfo.tm_wday;    // Sunday = 0, Monday = 1
  int currentMin = timeinfo.tm_hour * 60 + timeinfo.tm_min;

  int activeIndex = -1;

  for (int i = 0; i < totalPeriods; i++) {
    if (timetable[i].day == today &&
        currentMin >= timetable[i].startMin &&
        currentMin < timetable[i].endMin) {
      activeIndex = i;
      break;
    }
  }

  lcd.clear();

  if (activeIndex == -1) {
    lcd.setCursor(0, 0);
    lcd.print("Lab1: FREE");

    int nextIndex = findNextClass(today, currentMin);

    lcd.setCursor(0, 1);

    if (nextIndex == -1) {
      lcd.print("No next class");
    } else {
      printNextClass(nextIndex);
    }
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Occupied ");
    lcd.print(timetable[activeIndex].subject);

    lcd.setCursor(0, 1);
    lcd.print(timetable[activeIndex].section);
    lcd.print(" ");
    lcd.print(timetable[activeIndex].teacher);
  }

  delay(3000);
}

int findNextClass(int today, int currentMin) {
  int nextIndex = -1;
  int smallestGap = 100000;

  for (int i = 0; i < totalPeriods; i++) {
    int daysAhead = timetable[i].day - today;

    if (daysAhead < 0) {
      daysAhead = daysAhead + 7;
    }

    int gap = daysAhead * 1440 + timetable[i].startMin - currentMin;

    if (gap > 0 && gap < smallestGap) {
      smallestGap = gap;
      nextIndex = i;
    }
  }

  return nextIndex;
}

void printNextClass(int index) {
  String dayName = getDayName(timetable[index].day);

  int h = timetable[index].startMin / 60;
  int m = timetable[index].startMin % 60;

  lcd.print(dayName);
  lcd.print(" ");

  if (h < 10) lcd.print("0");
  lcd.print(h);
  lcd.print(":");
  if (m < 10) lcd.print("0");
  lcd.print(m);

  lcd.print(" ");
  lcd.print(timetable[index].subject);
}

String getDayName(int day) {
  if (day == 1) return "Mon";
  if (day == 2) return "Tue";
  if (day == 3) return "Wed";
  if (day == 4) return "Thu";
  if (day == 5) return "Fri";

  return "---";
}