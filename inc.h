#define SECRET_SSID "walle"
#define SECRET_PASS "uxHA4Nc2s"

// Flush the serial buffer
void serial_flush(void);

// read input commands
void readstring();
int extractNumber(String inStr);
bool containsStr(String inStr, String substr);
void handleInput(String iput);
void printBytes(String bStr);
void setServo(int newpos, int serv);
void test(int serv);
void setServo(int newpos);
void runPro();