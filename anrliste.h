#define DPROG "anrliste"

class anrufcl
{
  public:
  std::string id; //Id
  std::string type; //Type
  std::string caller; //Caller
  std::string called; //Called
  std::string callednumber; //CalledNumber
  std::string name; //Name
  std::string numbertype;
  std::string device;
  std::string port;
  std::string date;
  std::string duration;
  std::string count;
};
//α
class hhcl:public hcl
{
 private:
 public:
  uchar obvi=0; // ob Konfigurationsdatei editiert werden soll
	uchar obvs=0;   // ob Quelldateien bearbeitet werden sollen
	string host="localhost";  // fuer MySQL/MariaDB
	string dbq="faxe"; // Datenbank
	string tabelle  //ω
		="anrufe" // MariaDB-Tabelle fuer Anrufjournal
		;  //α
	string muser; // Benutzer fuer Mysql/MariaDB
	string mpwd;  // Passwort fuer Mysql/MariaDB //ω
	string fbusr; // User für Fritzbox
	string fbpwd; // Password für Fritzbox
	const size_t maxconz=12;//aktc: 0=... //α
	uchar keineverarbeitung=0; // wenn cronminuten geaendert werden sollen, vorher abkuerzen
	DB* My=0;
 private:
	void lgnzuw();
 public:
  hhcl(const int argc, const char *const *const argv);
  ~hhcl();
	void pruefggfmehrfach();
	int  initDB();
	int  pruefDB(const string& db);
	void pruefanrufe(DB *My, const string& tabelle, const int obverb, const int oblog, const uchar direkt=0);
	void getcommandl0();
	void VorgbAllg();
	void VorgbSpeziell()
#ifdef VOMHAUPTCODE
		__attribute__((weak)) // implementationsspezifische Vorgaben, Modul vgb.cpp)
#endif
		;
	void MusterVorgb();
	void lieskonfein(const string& dprog);
	int getcommandline();
	void rueckfragen(); //ω
	int holanr();
	void autokonfschreib(); //α
	void zeigueberschrift();
}; // class hhcl //ω
