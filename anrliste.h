#define DPROG "anrliste"
// fuer verschiedene Sprachen //α
enum T_      
{
	T_virtVorgbAllg,
	T_pvirtVorgbSpeziell,
	T_virtMusterVorgb,
	T_pvirtvorrueckfragen,
	T_virtrueckfragen,
	T_virtpruefweiteres,
	T_virtmacherkl_Tx_lgn,
	T_Fehler_beim_Pruefen_von,
	T_st_k,
	T_stop_l,
	T_DPROG_anhalten,
	T_anhalten,
	T_Cron_Aufruf_von,
	T_gestoppt,
	T_n_k,
	T_dszahl_l,
	T_Zahl_der_aufzulistenden_Datensaetze_ist_zahl_statt,
	T_Datenbank_nicht_initialisierbar_breche_ab,
	T_Fuege_ein, //ω
	T_eindeutige_Identifikation,
	T_ID_aus_Fritzbox,
	T_Benutzer_fuer_Fritzbox,
	T_Passwort_fuer_Fritzbox,
	T_pruefanrufe,
	T_Anruftyp_1_ankommend_3_abgehend,
	T_Zeitpunkt_des_Verbindungsaufbaus,
	T_Name_des_Verbindungspartners,
	T_Rufnummer_des_Verbindungspartners,
	T_Nebenstelle_hier,
	T_Eigene_Rufnummer,
	T_CalledNr,
	T_Nummerntyp,
	T_Port,
	T_Verbindungsdauer,
	T_Zahl,
	T_Telefonprotokoll_der_Fritzbox,
	T_Datensaetze_gelesen,
	T_Datensaetze_eingetragen,
	T_tabname_l,
	T_fbusr_k,
	T_fbusr_l,
	T_fbpwd_k,
	T_fbpwd_l,
	T_verwendet_fuer_die_Fritzbox_den_Benutzer_string_anstatt,
	T_verwendet_fuer_die_Fritzbox_das_Passwort_string,
	T_MAX //α
}; // enum T_ //ω

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
	void clear();
};

//α
class hhcl:public dhcl
{
	private: 
		string dszahl="30"; // Datensatzzahl fuer Tabellenausgaben
		string host="localhost";  // fuer MySQL/MariaDB
		//ω
	protected: //α
		string p1;
		int p2;
		string p3;
		uchar oblista=0;
		long listz=30; //ω
		string fbusr; // User für Fritzbox
		string fbpwd; // Password für Fritzbox
	public: //α //ω
		string tabname  //ω
			="anrufe" // MariaDB-Tabelle fuer Anrufjournal
			;  //α
	private: //α //ω
		void virttesterg(); //α
		void virtlieskonfein();
		void virtautokonfschreib();
		void anhalten(); //ω
	protected: //α
		// void virtlgnzuw(); // wird aufgerufen in: virtrueckfragen, parsecl, lieskonfein, hcl::hcl nach holsystemsprache
		void virtVorgbAllg();
		void pvirtVorgbSpeziell()
#ifdef VOMHAUPTCODE
			__attribute__((weak)) // implementationsspezifische Vorgaben, Modul vgb.cpp)
#endif
			;
		void virtinitopt(); // (programm-)spezifische Optionen
		void pvirtmacherkl();
		void virtMusterVorgb();
		void pvirtvorzaehler();
		void virtzeigversion(const string& ltiffv=nix);
		void pvirtvorrueckfragen();
		void virtrueckfragen();
		void pvirtvorpruefggfmehrfach();
		void virtpruefweiteres();
		void virtzeigueberschrift();
		void pvirtfuehraus();
		void virtschlussanzeige();
		void zeigdienste(); //ω
	public: //α
		hhcl(const int argc, const char *const *const argv);
		~hhcl();
		friend class fsfcl;
		void pruefanrufe(DB *My, const string& tabelle, const int obverb, const int oblog, const uchar direkt=0);
		int holanr();
}; // class hhcl //ω
