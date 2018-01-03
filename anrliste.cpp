#include "kons.h"
#include "DB.h"
#define VOMHAUPTCODE
#include "anrliste.h"
#include <curl/curl.h>

enum T_
{
	T_zu_schreiben,
	T_VorgbAllg,
	T_VorgbSpeziell,
	T_MusterVorgb,
	T_rueckfragen,
	T_autokonfschreib,
	T_pruefanrufe,
	T_Anruftyp_1_ankommend_3_abgehend,
	T_Fehler_beim_Pruefen_von,
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
	T_eindeutige_Identifikation,
	T_ID_aus_Fritzbox,
	T_verwendet_die_Datenbank_auf_Host_string_anstatt_auf,
	T_verwendet_fuer_MySQL_MariaDB_den_Benutzer_string_anstatt,
	T_verwendet_fuer_MySQL_MariaDB_das_Passwort_string,
	T_verwendet_die_Datenbank_string_anstatt,
	T_verwendet_die_Tabelle_string_anstatt,
	T_Host_fuer_MySQL_MariaDB_Datenbank,
	T_Benutzer_fuer_MySQL_MariaDB,
	T_Passwort_fuer_MySQL_MariaDB,
	T_Datenbankname_fuer_MySQL_MariaDB_auf,
	T_Tabellenname_in,
	T_Benutzer_fuer_Fritzbox,
	T_Passwort_fuer_Fritzbox,
	T_Logverzeichnis,
	T_Logdateiname,
	Verbindung_zur_Datenbank_nicht_herstellbar,
	T_Breche_ab,
	T_pruefDB,
	T_host_k,
	T_host_l,
	T_muser_k,
	T_muser_l,
	T_mpwd_k,
	T_mpwd_l,
	T_db_k,
	T_datenbank_l,
	T_tb_k,
	T_tabelle_l,
	T_fbusr_k,
	T_fbusr_l,
	T_fbpwd_k,
	T_fbpwd_l,
	T_verwendet_fuer_die_Fritzbox_den_Benutzer_string_anstatt,
	T_verwendet_fuer_die_Fritzbox_das_Passwort_string,
	T_sqlv_k,
	T_sql_verbose_l,
	T_rf_k,
	T_rueckfragen_l,
	T_krf_k,
	T_keinerueckfragen_l,
	T_cm_k,
	T_cronminuten_l,
	T_nicht_erkannt,
	T_Liest_das_Fritzbox_Journal_Ueber_RogerRouter_aus_und_sammelt_es_in_einer_Datenbank,
	T_schreibe_Konfiguration,
	T_info_k,
	T_version_l,
	T_vi_k,
	T_vi_l,
	T_h_k,
	T_lh_k,
	T_hilfe_l,
	T_lhilfe_l,
	T_fgz_k,
	T_fgz_l,
	T_Zeigt_die_Programmversion_an,
	T_Konfigurations_u_Logdatei_bearbeiten_sehen,
	T_Erklaerung_haeufiger_Optionen,
	T_Erklaerung_aller_Optionen,
	T_Fuege_ein,
	T_Datensaetze_gelesen,
	T_Datensaetze_eingetragen,
	T_Alle_wieviel_Minuten_soll,
	T_aufgerufen_werden_0_ist_gar_nicht,
	T_Bildschirmausgabe_mit_SQL_Befehlen,
	T_alle_Parameter_werden_abgefragt_darunter_einige_hier_nicht_gezeigte,
	T_keine_Rueckfragen_zB_aus_Cron,
	T_autoupd_k,
	T_autoupd_l,
	T_Programm_automatisch_aktualisieren,
	T_Sollen_neue_Programmversionen_von,
	T_automatisch_installiert_werden,
	T_zeigvers,
	T_Logpfad,
	T_oblog,
	T_Oblog,
	T_Aufrufintervall,
	T_kein_Aufruf,
	T_Minute,
	T_MAX
}; // enum T_

char const *DPROG_T[T_MAX+1][SprachZahl]={
	// T_zu_schreiben
	{"zu schreiben: ","must write: "},
	// T_VorgbAllg
	{"VorgbAllg()","generalprefs()"},
	// T_VorgbSpeziell
	{"VorgbSpeziell()","specialprefs()"},
	// T_MusterVorgb
	{"MusterVorgb()","sampleprefs"},
	// T_rueckfragen
	{"rueckfragen()","callbacks()"},
	// T_autokonfschreib
	{"autokonfschreib()","autoconfwrite()"},
	// T_pruefanrufe
	{"pruefanrufe()","checkcalls()"},
	// T_Anruftyp_1_ankommend_3_abgehend
	{"Anruftyp: 1=ankommend, 2=ankommend im Abwesenheit, 3=abgehend","type of call: 1=incoming, 2=incoming absent, 3=outgoing"},
	//	T_Fehler_beim_Pruefen_von
	{"Fehler beim Pruefen von: ","Error while examining: "},
	// T_Zeitpunkt_des_Verbindungsaufbaus
	{"Zeitpunkt des Verbindungsaufbaus","Start time of the connection"},
	// T_Name_des_Verbindungspartners
	{"Name des Verbindungspartners","Name of the Couterpart"},
	// T_Rufnummer_des_Verbindungspartners
	{"Rufnummer des Verbindungspartners","Dial number of the counterpart"},
	// T_Nebenstelle_hier
	{"Nebenstelle hier","party line here"},
	// T_Eigene_Rufnummer
	{"Eigene Rufnummer","Own calling number"},
	// T_CalledNr
	{"angerufene Nr, meist überzählig","Called number, mostly redundant"},
	// T_Nummerntyp
	{"Nummberntyp","number type"},
	// T_Port
	{"Port","port"},
	// T_Verbindungsdauer
	{"Verbindungsdauer","Connection duration"},
	// T_Zahl
	{"Zahl","count"},
	// T_Telefonprotokoll_der_Fritzbox
	{"Telefonprotokoll der Fritzbox","Connection journal of the fritzbox"},
	// T_eindeutige_Identifikation
	{"eindeutige Identifiaktion","unique ID"},
	// T_ID_aus_Fritzbox
	{"ID aus der Fritzbox","ID from the fritzbox"},
	// T_verwendet_die_Datenbank_auf_Host_string_anstatt_auf
	{"verwendet die Datenbank auf Host <string> anstatt auf","takes the database on host <string> instead of"},
	// T_verwendet_fuer_MySQL_MariaDB_den_Benutzer_string_anstatt
	{"verwendet fuer MySQL/MariaDB den Benutzer <string> anstatt","takes the user <string> for MySQL/MariaDB instead of"},
	// T_verwendet_fuer_MySQL_MariaDB_das_Passwort_string
	{"verwendet fuer MySQL/MariaDB das Passwort <string>","takes the password <string> for MySQL/MariaDB"},
	// T_verwendet_die_Datenbank_string_anstatt
	{"verwendet die Datenbank <string> anstatt","uses the database <string> instead of"},
	// T_verwendet_die_Tabelle_string_anstatt
	{"verwendet die Tabelle <string> anstatt","uses the table <string> instead of"},
	// T_Host_fuer_MySQL_MariaDB_Datenbank
	{"Host fuer MySQL/MariaDB-Datenbank","host for mysql/mariadb-database"},
	// T_Benutzer_fuer_MySQL_MariaDB,
	{"Benutzer fuer MySQL/MariaDB:","user for mysql/mariadb:"},
	// T_Passwort_fuer_MySQL_MariaDB,
	{"Passwort fuer MySQL/MariaDB (Achtung: nur schwach verschluesselt!)","password for mysql/mariadb (caution: only weakly encrypted!)"},
	// T_Datenbankname_fuer_MySQL_MariaDB_auf
	{"Datenbankname fuer MySQL/MariaDB auf '","database name for mysql/mariabd on '"},
	// T_Tabellenname_in
	{"Tabellenname in '","table name in '"},
	// T_Benutzer_fuer_Fritzbox,
	{"Benutzer fuer Fritzbox","password for fritzbox"},
	// T_Passwort_fuer_Fritzbox,
	{"Passwort fuer Fritzbox (Achtung: nur schwach verschluesselt!)","password for fritzbox (caution: only weakly encrypted!)"},
	// T_Logverzeichnis
	{"Logverzeichnis","log directory"},
	// T_Logdateiname
	{"Logdateiname","log file name"},
	// Verbindung_zur_Datenbank_nicht_herstellbar
	{"Verbindung zur Datenbank nicht herstellbar, fehnr: ","Connection to the database could not be established, errnr: "},
	// T_Breche_ab
	{". Breche ab.","Stopping."},
	// T_pruefDB
	{"pruefDB(","checkDB("},
	// T_host_k
	{"host","host"},
	// T_host_l
	{"host","host"},
	// T_muser_k
	{"muser","muser"},
	// T_muser_l
	{"muser","muser"},
	// T_mpwd_k
	{"mpwd","mpwd"},
	// T_mpwd_l
	{"mpwd","mpwd"},
	// T_db_k
	{"db","db"},
	// T_datenbank_l
	{"datenbank","database"},
	// T_tb_k,
	{"tb","tb"},
	// T_tabelle_l,
	{"tabelle","table"},
	// T_fbusr_k,
	{"fbusr","fbusr"},
	// T_fbusr_l,
	{"fbusr","fbusr"},
	// T_fbpwd_k,
	{"fbpwd","fbpwd"},
	// T_fbpwd_l,
	{"fbpwd","fbpwd"},
	// T_verwendet_fuer_die_Fritzbox_den_Benutzer_string_anstatt
	{"verwendet fuer die Fritzbox den Benutzer <string> anstatt","takes the user <string> for the fritzbox instead of"},
	// T_verwendet_fuer_die_Fritzbox_das_Passwort_string
	{"verwendet fuer die Fritzbox das Passwort <string>","takes the password <string< for the fritzbox"},
	// T_sqlv_k
	{"sqlw","sqlv"},
	// T_sql_verbose_l
	{"sql-wortreich","sql-verbose"},
	// T_rf_k
	{"rf","ia"},
	// T_rueckfragen_l
	{"rueckfragen","interactive"},
	// T_krf_k
	{"krf","noia"},
	// T_keinerueckfragen_l
	{"keinerueckfragen","nointeraction"},
	// T_cm_k
	{"cm","cm"},
	// T_cronminuten_l
	{"cronminuten","cronminutes"},
	// T_nicht_erkannt
	{" nicht erkannt!"," not identified!"},
	// T_Liest_das_Fritzbox_Journal_Ueber_RogerRouter_aus_und_sammelt_es_in_einer_Datenbank
	{"Liest das Fritzbox Journal über RogerRouter aus und sammelt es einer Datenbank",
		"Reads the fritzbox journal via roger router and collects in in a database"},
	// T_schreibe_Konfiguration
	{"schreibe Konfiguration!","writing configuration!"},
	// T_info_k
	{"info","info"},
	// T_version_l
	{"version","version"},
	// T_vi_k
	{"vi","vi"},
	// T_vi_l
	{"vi","vi"},
	// T_vc_k
	{"h","h"},
	// T_lh_k
	{"lh","lh"},
	// T_hilfe_l
	{"hilfe","help"},
	// T_lhilfe_l
	{"langhilfe","longhelp"},
	// T_fgz_k
	{"?","?"},
	// T_fgz_l,
	{"??","??"},
	// T_Zeigt_die_Programmversion_an
	{"Zeigt die Programmversion an","shows the program version"},
	// T_Konfigurations_u_Logdatei_bearbeiten_sehen
	{"Konfigurations- u.Logdatei bearbeiten/sehen (beenden mit ':qa')","edit/view configuration and log file (finish with ':qa')"},
	// 	T_Erklaerung_haeufiger_Optionen
	{"Erklärung häufiger Optionen","Explanation of frequent options"},
	// T_Erklaerung_aller_Optionen
	{"Erklärung aller Optionen","Explanation of all options"},
	// T_Fuege_ein
	{"Füge ein: ","Inserting: "},
	// T_Datensaetze_gelesen
	{" Datensaetze gelesen"," data sets read"},
	// T_Datensaetze_eingetragen
	{" Datensaetze eingetragen"," data sets inserted"},
	// T_Alle_wieviel_Minuten_soll
	{"alle wieviel Minuten soll ","every how many minutes shall "},
	// T_aufgerufen_werden_0_ist_gar_nicht]
	{" ueber crontab aufgerufen werden (0=gar nicht), anstatt ", " be called in crontab (0=not at all), instead of "},
	// T_Bildschirmausgabe_mit_SQL_Befehlen
	{"Bildschirmausgabe mit SQL-Befehlen","screen output with SQL commands"},
	// T_alle_Parameter_werden_abgefragt_darunter_einige_hier_nicht_gezeigte
	{"alle Parameter werden abgefragt (darunter einige hier nicht gezeigte)","all parameters will be prompted (some of them not shown here)"},
	// T_keine_Rueckfragen_zB_aus_Cron
	{"keine Rueckfragen, z.B. für Aufruf aus cron","no questions, e.g. for a call of " DPROG " within cron"},
	// 	T_autoupd_k,
	{"autoakt","autoupd"},
	// 	T_autoupd_l,
	{"autoaktual","autoupdate"},
	// T_Programm_automatisch_aktualisieren
	{"Programm automatisch aktualisieren","Update program automatically"},
	// T_Sollen_neue_Programmversionen_von
	{"Sollen neue Programmversionen von ","Shall new versions of "},
	// T_automatisch_installiert_werden
	{" automatisch installiert werden?"," be automatically installed?"},
	// T_zeigvers
	{"zeigvers","showvers"},
	// T_Logpfad,
	{"Logpfad: '","Log path: '"},
	// T_oblog,
	{"' (oblog: ","' (with logging: "},
	// T_Oblog,
	{"Oblog (ausführliche Protokollierung): ","Log (detailled logging): "},
	// T_Aufrufintervall
	{"; Aufrufintervall: ","; (cron) call interval: "},
	// T_kein_Aufruf
	{"kein cron-Aufruf","no cron call"},
	// T_Minute
	{" Minute"," minute"},
 {"",""}
}; // char const *DPROG_T[T_MAX+1][SprachZahl]=

class TxB Tx((const char* const* const* const*)DPROG_T);

uchar ZDB=0; // fuer Zusatz-Debugging (SQL): ZDB 1, sonst: 0
const char *logdt="/var/log/" DPROG "vorgabe.log";//darauf wird in kons.h verwiesen; muss dann auf lgp zeigen;
const string& pwk = "4893019320jfdksalö590ßs89d0qÃ9m0943Ã09Ãax"; // fuer Antlitzaenderung

using namespace std;

#ifdef mitpostgres 
const DBSTyp myDBS=Postgres;
#else // mitpostgre
const DBSTyp myDBS=MySQL;
#endif // mitpostgres else


hhcl::hhcl(const int argc, const char *const *const argv):hcl(argc,argv)
{
} // hhcl::hhcl

hhcl::~hhcl()
{
} // hhcl::~hhcl

// wird aufgerufen in: rueckfragen, als virtualle Funktion von hcl::gcl0()
void hhcl::lgnzuw()
{
 hcl::lgnzuw();
 Txd.lgn=Tx.lgn=Txk.lgn;
} // void hhcl::lgnzuw

// wird aufgerufen in: main
void hhcl::getcommandl0()
{
 if (obverb) {
  cout<<violett<<"getcommandl0()"<<schwarz<<endl;
  obverb=0;
 }
 // Reihenfolge muss koordiniert werden mit lieskonfein und rueckfragen
 const char* const sarr[]={"language","host","muser","mpwd","datenbank","tabelle","fbusr","fbpwd","cronminut","autoupd","logvz","logdname","oblog"};
 agcnfA.initd(sarr,sizeof sarr/sizeof *sarr);
 gcl0();
} // getcommandl0

void hhcl::VorgbAllg()
{
 Log(violetts+Tx[T_VorgbAllg]+schwarz);
 cronminut="2";
 autoupd=1;
} // void hhcl::VorgbAllg

void hhcl::VorgbSpeziell()
{
 Log(violetts+Tx[T_VorgbSpeziell]+schwarz);
 MusterVorgb();
} // void hhcl::VorgbSpeziell

void hhcl::MusterVorgb()
{
 Log(violetts+Tx[T_MusterVorgb]+schwarz);
} // void hhcl::MusterVorgb

// wird aufgerufen in: main
void hhcl::lieskonfein(const string& dprog)
{
 hcl::lieskonfein(dprog);
 lfd++;
 if (agcnfA[lfd].gelesen) agcnfA[lfd].hole(&host); else rzf=1; lfd++;
 if (agcnfA[lfd].gelesen) agcnfA[lfd].hole(&muser); else rzf=1; lfd++;
 if (agcnfA[lfd].gelesen) mpwd=XOR(string(agcnfA[lfd].wert),pwk); else rzf=1; lfd++;
 if (agcnfA[lfd].gelesen) agcnfA[lfd].hole(&dbq); else rzf=1; lfd++;
 if (agcnfA[lfd].gelesen) agcnfA[lfd].hole(&tanrufe); else rzf=1; lfd++;
 if (agcnfA[lfd].gelesen) agcnfA[lfd].hole(&fbusr); else rzf=1; lfd++;
 if (agcnfA[lfd].gelesen) fbpwd=XOR(string(agcnfA[lfd].wert),pwk); else rzf=1; lfd++;
 if (agcnfA[lfd].gelesen) agcnfA[lfd].hole(&cronminut); else rzf=1; lfd++;
 if (agcnfA[lfd].gelesen) agcnfA[lfd].hole(&autoupd); else rzf=1; lfd++;
 if (logvneu) agcnfA[lfd].setze(&logvz);
 if (agcnfA[lfd].gelesen) agcnfA[lfd].hole(&logvz); else rzf=1; lfd++;
 if (logdneu) agcnfA[lfd].setze(&logdname);
 if (agcnfA[lfd].gelesen) agcnfA[lfd].hole(&logdname); else rzf=1; lfd++;
 if (agcnfA[lfd].gelesen) agcnfA[lfd].hole(&oblog); else rzf=1; lfd++;
 setzlog();
 if (nrzf) rzf=0;
} // void hhcl::lieskonfein

//wird aufgerufen in: main
int hhcl::getcommandline()
{
 Log(violetts+"getcommandline()"+schwarz);
 opts.push_back(/*2*/optioncl(T_host_k,T_host_l,&Tx, T_verwendet_die_Datenbank_auf_Host_string_anstatt_auf,0,&host,psons,&agcnfA,"host",&obkschreib));
 opts.push_back(/*2*/optioncl(T_muser_k,T_muser_l,&Tx, T_verwendet_fuer_MySQL_MariaDB_den_Benutzer_string_anstatt,0,&muser,psons,&agcnfA, "muser",&obkschreib));
 opts.push_back(/*2*/optioncl(T_mpwd_k,T_mpwd_l,&Tx, T_verwendet_fuer_MySQL_MariaDB_das_Passwort_string,0,&mpwd,psons,&agcnfA,"mpwd",&obkschreib));
 opts.push_back(/*2*/optioncl(T_db_k,T_datenbank_l,&Tx, T_verwendet_die_Datenbank_string_anstatt,0,&dbq,psons,&agcnfA,"datenbank",&obkschreib));
 opts.push_back(/*2*/optioncl(T_tb_k,T_tabelle_l,&Tx, T_verwendet_die_Tabelle_string_anstatt,0,&tanrufe,psons,&agcnfA,"tabelle",&obkschreib));
 opts.push_back(/*2*/optioncl(T_fbusr_k,T_fbusr_l,&Tx, T_verwendet_fuer_die_Fritzbox_den_Benutzer_string_anstatt,0,&fbusr,psons,&agcnfA, "fbusr",&obkschreib));
 opts.push_back(/*2*/optioncl(T_fbpwd_k,T_fbpwd_l,&Tx, T_verwendet_fuer_die_Fritzbox_das_Passwort_string,0,&fbpwd,psons,&agcnfA,"fbpwd",&obkschreib));
 opts.push_back(/*3*/optioncl(T_cm_k,T_cronminuten_l,&Tx,T_Alle_wieviel_Minuten_soll,1,&meinname,T_aufgerufen_werden_0_ist_gar_nicht,&cronminut,
			 pzahl, &agcnfA,"cronminut",&obkschreib));
 opts.push_back(/*4*/optioncl(T_autoupd_k,T_autoupd_l, &Tx, T_Programm_automatisch_aktualisieren,1,&autoupd,1,&agcnfA,"autoupd",&obkschreib));
 opts.push_back(/*4*/optioncl(T_sqlv_k,T_sql_verbose_l, &Tx, T_Bildschirmausgabe_mit_SQL_Befehlen,1,&ZDB,1));
 opts.push_back(/*4*/optioncl(T_rf_k,T_rueckfragen_l, &Tx, T_alle_Parameter_werden_abgefragt_darunter_einige_hier_nicht_gezeigte,1,&rzf,1));
 opts.push_back(/*4*/optioncl(T_krf_k,T_keinerueckfragen_l, &Tx, T_keine_Rueckfragen_zB_aus_Cron,1,&nrzf,1));
 opts.push_back(/*4*/optioncl(T_info_k,T_version_l, &Tx, T_Zeigt_die_Programmversion_an, 1, &zeigvers,1));
 opts.push_back(/*4*/optioncl(T_vi_k,T_vi_l, &Tx, T_Konfigurations_u_Logdatei_bearbeiten_sehen, 1, &obvi,1));
 opts.push_back(/*4*/optioncl(T_h_k,T_hilfe_l, &Tx, T_Erklaerung_haeufiger_Optionen, 1, &obhilfe,1));
 opts.push_back(/*4*/optioncl(T_lh_k,T_lhilfe_l, &Tx, T_Erklaerung_aller_Optionen, 1, &obhilfe,2));
 opts.push_back(/*4*/optioncl(T_fgz_k,T_fgz_l, &Tx, -1, 1, &obhilfe,1));
 // hier wird die Befehlszeile ueberprueft:
 for(;optslsz<opts.size();optslsz++) {
	 for(size_t i=0;i<argcmv.size();i++) {
		 if (opts[optslsz].pruefpar(&argcmv,&i,&obhilfe,Tx.lgn)) {
			 if (opts[optslsz].kurzi==T_cm_k) { // cronminuten
				 keineverarbeitung=1;
				 cmeingegeben=1;
			 }
			 else if (opts[optslsz].kurzi==T_mpwd_k) {
				 const string pwdstr=XOR(mpwd,pwk);
				 agcnfA.setze(string(Tx[T_mpwd_k]),pwdstr);
			 } // 				if (opts[optslsz].kurzi==T_mpwd_k)
			 else if (opts[optslsz].kurzi==T_fbpwd_k) {
				 const string pwdstr=XOR(fbpwd,pwk);
				 agcnfA.setze(string(Tx[T_fbpwd_k]),pwdstr);
			 } // 				if (opts[optslsz].kurzi==T_mpwd_k)
			 break;
		 } //       if (opts[optslsz].pruefpar(&argcmv,&i,&obhilfe,Tx.lgn))
	 } // for(size_t i=0;i<argcmv.size();i++) 
 } //   for(;optslsz<opts.size();optslsz++)
 if (nrzf||obhilfe>2) rzf=0; // 3 oder 4
 for(size_t i=0;i<argcmv.size();i++) {
	 if (!argcmv[i].agef) {
		 ::Log(rots+"Parameter: "+gruen+argcmv[i].argcs+rot+Tx[T_nicht_erkannt]+schwarz,1,1);
		 if (!obhilfe) obhilfe=1;
	 } //     if (!argcmv[i].agef)
 } //   for(size_t i=0;i<argcmv.size();i++)
	stringstream erkl;
	erkl<<blau<<Tx[T_Liest_das_Fritzbox_Journal_Ueber_RogerRouter_aus_und_sammelt_es_in_einer_Datenbank]<<schwarz;
 if (zeighilfe(&erkl)) 
	 return 1;
	Log(violetts+Txk[T_Ende]+"getcommandline()"+schwarz);
 return 0;
} // int hhcl::getcommandline

// wird aufgerufen in: main
void hhcl::rueckfragen()
{
 Log(violetts+Tx[T_rueckfragen]+schwarz);
 if (rzf) {
  int lfd=-1;
  const char *const locale = setlocale(LC_CTYPE,"");
  if (langu.empty()) if (locale) if (strchr("defi",locale[0])) langu=locale[0];
  vector<string> sprachen={"e","d"/*,"f","i"*/};
  if (agcnfA[++lfd].wert.empty()||rzf) {
   langu=Tippstrs(sprachstr.c_str()/*"Language/Sprache/Lingue/Lingua"*/,&sprachen,&langu);
   lgnzuw();
   agcnfA[lfd].setze(&langu);
  } // if (agcnfA
	if (agcnfA[++lfd].wert.empty() || rzf) {
		host=Tippstr(Tx[T_Host_fuer_MySQL_MariaDB_Datenbank],&host);
		agcnfA[lfd].setze(&host);
	} //     if (agcnfA[++lfd].wert.empty() || rzf)
	if (agcnfA[++lfd].wert.empty() || rzf) {
		const string Frage=Tx[T_Benutzer_fuer_MySQL_MariaDB];
		muser=Tippstr(Frage.c_str(),&muser);
		agcnfA[lfd].setze(&muser);
	} //     if (agcnfA[++lfd].wert.empty() || rzf)
	if (agcnfA[++lfd].wert.empty() || rzf) {
		string mpw2;
		mpwd.clear();
		do {
			mpwd=Tippstr(string(Tx[T_Passwort_fuer_MySQL_MariaDB])+Txk[T_fuer_Benutzer]+dblau+muser+schwarz+"'",&mpwd);
			mpw2=Tippstr(string(Tx[T_Passwort_fuer_MySQL_MariaDB])+Txk[T_fuer_Benutzer]+dblau+muser+schwarz+"'"+" ("+Txk[T_erneute_Eingabe]+")",&mpw2);
		} while (mpwd!=mpw2);
		const string pwdstr=XOR(mpwd,pwk);
		agcnfA[lfd].setze(&pwdstr);
	} // 		if (agcnfA[++lfd].wert.empty() || rzf)
	if (agcnfA[++lfd].wert.empty() || rzf) {
		dbq=Tippstr(string(Tx[T_Datenbankname_fuer_MySQL_MariaDB_auf])+dblau+host+schwarz+"'",&dbq);
		agcnfA[lfd].setze(&dbq);
	} //     if (agcnfA[++lfd].wert.empty() || rzf)
	if (agcnfA[++lfd].wert.empty() || rzf) {
		tanrufe=Tippstr(string(Tx[T_Tabellenname_in])+dblau+dbq+schwarz+"'",&tanrufe);
		agcnfA[lfd].setze(&tanrufe);
	} //     if (agcnfA[++lfd].wert.empty() || rzf)
	if (agcnfA[++lfd].wert.empty() || rzf) {
		const string Frage=Tx[T_Benutzer_fuer_Fritzbox];
		fbusr=Tippstr(Frage.c_str(),&fbusr);
		agcnfA[lfd].setze(&fbusr);
	} //     if (agcnfA[++lfd].wert.empty() || rzf)
	if (agcnfA[++lfd].wert.empty() || rzf) {
		string fbpw2;
		fbpwd.clear();
		do {
			fbpwd=Tippstr(string(Tx[T_Passwort_fuer_Fritzbox])+Txk[T_fuer_Benutzer]+dblau+fbusr+schwarz+"'",&fbpwd);
			fbpw2=Tippstr(string(Tx[T_Passwort_fuer_Fritzbox])+Txk[T_fuer_Benutzer]+dblau+fbusr+schwarz+"'"+" ("+Txk[T_erneute_Eingabe]+")",&fbpw2);
		} while (fbpwd!=fbpw2);
		const string pwdstr=XOR(fbpwd,pwk);
		agcnfA[lfd].setze(&pwdstr);
	} // 		if (agcnfA[++lfd].wert.empty() || rzf)
	if (agcnfA[++lfd].wert.empty() || rzf) {
		cronminut=Tippzahl(Tx[T_Alle_wieviel_Minuten_soll]+meinname+Tx[T_aufgerufen_werden_0_ist_gar_nicht],&cronminut);
		agcnfA[lfd].setze(&cronminut);
	}
	if (agcnfA[++lfd].wert.empty() || rzf) {
		autoupd=Tippob(Tx[T_Sollen_neue_Programmversionen_von]+meinname+Tx[T_automatisch_installiert_werden],autoupd?Txk[T_j_af]:"n");
		agcnfA[lfd].setze(&autoupd);
	}
	if (agcnfA[++lfd].wert.empty() || rzf) {
		logvz=Tippverz(Tx[T_Logverzeichnis],&logvz);
		agcnfA[lfd].setze(&logvz);
	}
	if (agcnfA[++lfd].wert.empty() || rzf) {
		logdname=Tippstr(Tx[T_Logdateiname],&logdname);
		agcnfA[lfd].setze(&logdname);
	}
	setzlog();
	if (agcnfA[++lfd].wert.empty() || rzf) {
		oblog=Tippzahl(Tx[T_Oblog],oblog);
		agcnfA[lfd].setze(&oblog);
	} // 	if (agcnfA[++lfd].wert.empty() || rzf)
 } // if (rzf)
} // void hhcl::rueckfragen()

// wird aufgerufen in: main
void hhcl::autokonfschreib()
{
	Log(violetts+Tx[T_autokonfschreib]+schwarz+", "+Tx[T_zu_schreiben]+((rzf||obkschreib)?Txk[T_ja]:Txk[T_nein]));
	if (rzf||obkschreib) {
	 Log(gruens+Tx[T_schreibe_Konfiguration]+schwarz);
 } // if (rzf||obkschreib)
 schlArr *ggcnfAp[1]={&agcnfA};
 multischlschreib(akonfdt, ggcnfAp, sizeof ggcnfAp/sizeof *ggcnfAp, mpfad);
 chmod(akonfdt.c_str(),S_IRWXU);
} // void hhcl::autokonfschreib

// wird aufgerufen in: main
void hhcl::zeigueberschrift()
{
	char buf[20]; snprintf(buf,sizeof buf,"%.5f",versnr);
 ::Log(schwarzs+Txk[T_Programm]+blau+mpfad+schwarz+", V: "+blau+buf+schwarz
			+(crongeprueft?
				Tx[T_Aufrufintervall]+blaus
				+(vorcm!=cronminut&&!(vorcm.empty()&&cronminut=="0")?((vorcm.empty()?Txk[T_gar_nicht]:vorcm)+" -> "):"")
				+(cronminut=="0"?Tx[T_kein_Aufruf]+schwarzs:cronminut+schwarz+(cronminut=="1"?Tx[T_Minute]:Txk[T_Minuten])):
				"")
		 ,1,1);
} // void hhcl::zeigueberschrift

void hhcl::pruefggfmehrfach()
{
	if (!obhilfe &&!obvi &&!zeigvers) {
		pruefmehrfach(meinname,nrzf);
	}
} // void hhcl::pruefggfmehrfach()


static int writer(char *data, size_t size, size_t nmemb, std::string *writerData)
{
  if(writerData == NULL)
    return 0;

  writerData->append(data, size*nmemb);

  return size * nmemb;
}

size_t holraus(const std::string xml,std::string tag,std::string *ergp,size_t anf=0)
{
  const std::string von="<"+tag+">", bis="</"+tag+">";
  if (ergp) {
    ergp->clear();
    size_t p1=xml.find(von,anf);
    if (p1!=std::string::npos) {
      p1+=von.length();
      size_t p2=xml.find(bis,p1);
      if (p2!=std::string::npos) {
        *ergp=xml.substr(p1,p2-p1);
        return p2+bis.length();
      }
    }
  }
  return 0;
} // size_t holraus(const std::string xml,std::string tag,std::string *ergp;size_t anf=0)

// ermittelt aus test3.sh mit curl ... --libcurl test3.c
int fragurl(const std::string url, const std::string cred, const std::string servT, const std::string action,const std::string item, std::string* bufp)
{
  //std::cout<<"url: "<<url<<std::endl;
  CURL *hnd = NULL;
  CURLcode code;
  static char errorBuffer[CURL_ERROR_SIZE];
  bufp->clear();
  struct curl_slist *slist1=0;
  slist1 = curl_slist_append(slist1, "Content-Type: text/xml; charset=\"utf-8\"");
  slist1 = curl_slist_append(slist1, ("SoapAction: "+servT+"#"+action).c_str());
  hnd = curl_easy_init();
  if(hnd == NULL) {
    fprintf(stderr, "Failed to create CURL connection\n");
    exit(EXIT_FAILURE);
  }
  curl_easy_setopt(hnd, CURLOPT_URL, url.c_str());
  curl_easy_setopt(hnd, CURLOPT_USERPWD, cred.c_str());
  std::string postfield="<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<s:Envelope s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"\nxmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\">\n<s:Body>\n<u:"+action+" xmlns:u=\""+servT+"\">\n<></>\n</u:"+action+">\n</s:Body>\n</s:Envelope>";
  if ((code=curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, postfield.c_str()))!=CURLE_OK) {
    fprintf(stderr, "Fehler bei postfield [%s]\n", errorBuffer);
    return false;
  }
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)postfield.length());
  curl_easy_setopt(hnd, CURLOPT_USERAGENT, "curl/7.37.0");
  curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, slist1);
  curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
  curl_easy_setopt(hnd, CURLOPT_HTTPAUTH, (long)CURLAUTH_ANY);
  curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYPEER, 0L);
  curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYHOST, 0L);
  curl_easy_setopt(hnd, CURLOPT_IPRESOLVE, 1L);
  curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);
  curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, writer);
  curl_easy_setopt(hnd, CURLOPT_WRITEDATA , bufp);
  curl_easy_setopt(hnd, CURLOPT_ERRORBUFFER, errorBuffer);
  // Retrieve content for the URL
  code = curl_easy_perform(hnd);
  curl_easy_cleanup(hnd);
  if(code != CURLE_OK) {
    fprintf(stderr, "Fehler beim Verbinden zu '%s' [%s]\n", url.c_str(), errorBuffer);
    exit(EXIT_FAILURE);
  }
  return 0;
} // string fragurl(const string url, const string cred, const string servT, const string action,const string item)

int holurl(const std::string url, std::string* bufp)
{
  //std::cout<<"url: "<<url<<std::endl;
  CURL *hnd = NULL;
  CURLcode code;
  static char errorBuffer[CURL_ERROR_SIZE];
  bufp->clear();
  hnd = curl_easy_init();
  if(hnd == NULL) {
    fprintf(stderr, "Failed to create CURL connection\n");
    exit(EXIT_FAILURE);
  }
  curl_easy_setopt(hnd, CURLOPT_URL, url.c_str());
  curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, writer);
  curl_easy_setopt(hnd, CURLOPT_WRITEDATA , bufp);
  curl_easy_setopt(hnd, CURLOPT_ERRORBUFFER, errorBuffer);
  // Retrieve content for the URL
  code = curl_easy_perform(hnd);
  curl_easy_cleanup(hnd);
  if(code != CURLE_OK) {
    fprintf(stderr, "Fehler beim Verbinden zu '%s' [%s]\n", url.c_str(), errorBuffer);
    exit(EXIT_FAILURE);
  }
  return 0;
} // int holurl(const std::string url, std::string* bufp)

int hhcl::holanr()
{
	const size_t aktc=0;
	size_t dsz=0,egz=0;
  std::vector<std::string> tz;
  tz.push_back("Id");
  tz.push_back("Type");
  tz.push_back("Caller");
  tz.push_back("Called");
  tz.push_back("CalledNumber");
  tz.push_back("Name");
  tz.push_back("Numbertype");
  tz.push_back("Device");
  tz.push_back("Port");
  tz.push_back("Date");
  tz.push_back("Duration");
  tz.push_back("Count");

  // Ensure one argument is given


  curl_global_init(CURL_GLOBAL_DEFAULT);

  // Initialize CURL connection

  std::string credentials=fbusr+":"+fbpwd;
  std::string FB="fritz.box:49000";
  std::string controlURL="/upnp/control/x_contact";
  std::string serviceType="urn:dslforum-org:service:X_AVM-DE_OnTel:1";
  std::string action="GetCallList";
  std::string item="NewCallListURL";
  /*
  if(!init(hnd, ("http://"+FB+controlURL).c_str())) {
    fprintf(stderr, "Connection initializion failed\n");
    exit(EXIT_FAILURE);
  }
  */
  std::string buffer,nurl;
  fragurl("http://"+FB+controlURL,credentials,serviceType,action,item,&buffer);

  //std::cout<<buffer<<std::endl;
  holraus(buffer,item,&nurl);
  holurl(nurl,&buffer);
  size_t pos=0,enr=0;
	RS rins(My); 
	while ((pos=holraus(buffer,"Call",&nurl,pos))) {
		stringstream ausg;
		ausg<<++enr<<": ";
		size_t ipos=0;
		tm vt({0});
		stringstream vts;
		anrufcl ar;
		for(size_t tzn=0;tzn<tz.size();tzn++) {
			std::string it;
			ipos=holraus(nurl,tz[tzn],&it,ipos);
			switch (tzn) {
				case 0: ar.id=it;break;
				case 1: ar.type=it;break;
				case 2: ar.caller=it;break;
				case 3: ar.called=it;break;
				case 4: ar.callednumber=it;break;
				case 5: ar.name=it;break;
				case 6: ar.numbertype=it;break;
				case 7: ar.device=it;break;
				case 8: ar.port=it;break;
				case 9: ar.date=it;
								strptime(it.c_str(),"%d.%m.%y %H:%M",&vt);
								vts<<put_time(&vt,"%Y-%m-%d %H:%M");
								break;
				case 10: ar.duration=it;break;
				case 11: ar.count=it;break;
			} // 			switch (tzn)
			ausg<<it<<";";
		} // 		for(size_t tzn=0;tzn<tz.size();tzn++)
		dsz++;
		ersetzAlle(ar.duration,":",".");
		RS such(My,"SELECT datum FROM `"+tanrufe+"` WHERE typ="+ar.type+" and Datum='"+vts.str()+"' and Name ='"+ar.name+"'"\
				" and Rufnummer=if(typ='3','"+ar.called+"','"+ar.caller+"')"\
				" and EigeneNr=if(typ='3','"+ar.caller+"','"+ar.called+"') and Dauer='"+ar.duration+"'",aktc,ZDB);//Nst wg. Zeichensatz weggel.
		if (!such.obfehl) {
			char*** cerg=such.HolZeile();
			if (!cerg || !*cerg) {
				vector<instyp> einf; // fuer alle Datenbankeinfuegungen
				einf.push_back(/*2*/instyp(My->DBS,"Id",ar.id));
				einf.push_back(/*2*/instyp(My->DBS,"Typ",ar.type));
				einf.push_back(/*2*/instyp(My->DBS,"Datum",&vt));
				einf.push_back(/*2*/instyp(My->DBS,"Name",ar.name));
				einf.push_back(/*2*/instyp(My->DBS,"Rufnummer",(ar.type=="3"?ar.called:ar.caller)));
				einf.push_back(/*2*/instyp(My->DBS,"Nebenstelle",ar.device));
				einf.push_back(/*2*/instyp(My->DBS,"EigeneNr",(ar.type=="3"?ar.caller:ar.called)));
				einf.push_back(/*2*/instyp(My->DBS,"angerNr",ar.callednumber));
				einf.push_back(/*2*/instyp(My->DBS,"Nummerntyp",ar.numbertype));
				einf.push_back(/*2*/instyp(My->DBS,"Port",ar.port));
				einf.push_back(/*2*/instyp(My->DBS,"Dauer",ar.duration));
				einf.push_back(/*2*/instyp(My->DBS,"Zahl",ar.count));
				// caus<<Tx[T_Fuege_ein]<<put_time(&vt,"%Y-%m-%d %H:%M")<<endl;
				rins.tbins(tanrufe,&einf,aktc,/*sammeln=*/1,/*oberb=*/ZDB,/*idp=*/0,/*eindeutig=*/0);  // einfuegen
				if (!rins.fnr)
					egz++;
				::Log(blaus+ausg.str()+schwarz,1,oblog);
			} else {
				Log(ausg.str());
			} // 					if (!cerg || !*cerg)
		} // 				if (!such.obfehl)
	} // 	while ((pos=holraus(buffer,"Call",&nurl,pos)))
	rins.tbins(tanrufe,0,aktc,/*sammeln=*/0,/*oberb=*/ZDB,/*idp=*/0,/*eindeutig=*/0);  // einfuegen
	::Log(blaus+ltoan(dsz)+schwarz+Tx[T_Datensaetze_gelesen],1,0);
	::Log(blaus+ltoan(egz)+schwarz+Tx[T_Datensaetze_eingetragen],1,0);
	// std::cout<<buffer<<std::endl;
	return EXIT_SUCCESS;
}

// wird aufgerufen in: main
int hhcl::initDB()
{
	Log(violetts+"initDB(), db: "+blau+dbq+schwarz);
	unsigned int fehler=0;
	if (dbq.empty()) {
		fehler=1046;
	} else {
		if (!My) {
			My=new DB(myDBS,linstp,host,muser,mpwd,maxconz,dbq,/*port=*/0,/*unix_socket=*/0,/*client_flag=*/0,obverb,oblog);
			if (My->ConnError) {
				delete My;
				My=0;
			} else {
				My->lassoffen=1;
			} // 			if (My->ConnError) else
		} // 		if (!My)
		fehler=My->fehnr;
	} // 	if (dbq.empty())
	if (fehler) {
		Log(rots+Tx[Verbindung_zur_Datenbank_nicht_herstellbar]+schwarz+ltoan(fehler)+rot+Tx[T_Breche_ab]+schwarz);
		return 1;
	} //   if (My->fehnr)
	return 0;
} // initDB

// wird aufgerufen in rueckfragen
int hhcl::pruefDB(const string& db)
{
	Log(violetts+Tx[T_pruefDB]+db+")"+schwarz);
	if (!My) {
		My=new DB(myDBS,linstp,host,muser,mpwd,maxconz,db,0,0,0,obverb,oblog,DB::defmycharset,DB::defmycollat,3,0);
		if (My->ConnError) {
			delete My;
			My=0;
		}else {
			My->lassoffen=1;
		}
	} // 	if (!My)
	return (My->fehnr); 
} // pruefDB

// wird aufgerufen in: main
void hhcl::pruefanrufe(DB *My, const string& tanrufe, const int obverb, const int oblog, const uchar direkt/*=0*/)
{
	Log(violetts+Tx[T_pruefanrufe]+schwarz,obverb,oblog);
	const size_t aktc=0;
	if (!direkt) {
		Feld felder[] = {
			Feld("eind","int","10","",Tx[T_eindeutige_Identifikation],/*obind*/1,/*obauto*/1/*,nnull*/),
			Feld("Id","int","10","",Tx[T_ID_aus_Fritzbox],1,0,1), // Id, (0)
			Feld("Typ","decimal","2","0",Tx[T_Anruftyp_1_ankommend_3_abgehend],1,0,1), // Type (1)
			Feld("Datum","datetime","0","0",Tx[T_Zeitpunkt_des_Verbindungsaufbaus],0,0,1), // Date (9)
			Feld("Name","varchar","1","",Tx[T_Name_des_Verbindungspartners],0,0,1), //Name (5)
			Feld("Rufnummer","varchar","1","",Tx[T_Rufnummer_des_Verbindungspartners],0,0,1), // bei Type 1 und 2 Caller (2), bei 3 Called (3)
			Feld("Nebenstelle","varchar","1","",Tx[T_Nebenstelle_hier],0,0,1), // Device (7)
			Feld("EigeneNr","varchar","1","",Tx[T_Eigene_Rufnummer],0,0,1), // bei Type 1 und 2 Called (3), bei 3 Caller (2)
			Feld("angerNr","varchar","1","",Tx[T_CalledNr],0,0,1), // CalledNumber (4)
			Feld("Nummerntyp","varchar","1","",Tx[T_Nummerntyp],0,0,1), // Numbertype (6)
			Feld("Port","varchar","1","",Tx[T_Port],0,0,1), // Port (8)
			Feld("Dauer","decimal","5","2",Tx[T_Verbindungsdauer],0,0,1), // Duration (10)
			Feld("Zahl","varchar","1","",Tx[T_Zahl],0,0,1), // Count (11)
		};
		Feld ifelder0[] = {Feld("Datum")};   Index i0("Datum",ifelder0,sizeof ifelder0/sizeof* ifelder0);
		Index indices[]={i0};
		// auf jeden Fall ginge "binary" statt "utf8" und "" statt "utf8_general_ci"
		Tabelle taba(My,tanrufe,felder,sizeof felder/sizeof* felder,indices,sizeof indices/sizeof *indices,
				Tx[T_Telefonprotokoll_der_Fritzbox]/*//,"InnoDB","utf8","utf8_general_ci","DYNAMIC"*/);
		if (taba.prueftab(aktc,obverb)) {
			Log(rots+Tx[T_Fehler_beim_Pruefen_von]+schwarz+tanrufe,1,1);
			exit(11);
		}
	} // if (!direkt)
} // int hhcl::pruefanrufe(DB *My, string touta, int obverb, int oblog, uchar direkt=0)


int main(int argc,char** argv)
{
 hhcl hhi(argc,argv); // hiesige Hauptinstanz
 /*//
 if (argc>1) {
 } // (argc>1)
 */
 hhi.getcommandl0(); // anfangs entscheidende Kommandozeilenparameter abfragen
 hhi.VorgbAllg();
 if (hhi.obhilfe==3) { // Standardausgabe gewaehrleisten
  hhi.MusterVorgb();
 } else {
  hhi.VorgbSpeziell(); // die Vorgaben, die in einer zusaetzlichen Datei mit einer weiteren Funktion "void hhcl::VorgbSpeziell()" ueberladbar sind
  hhi.lieskonfein(DPROG);
 } // if (hhi.obhilfe==3)
 hhi.lieszaehlerein(&hhi.aufrufe,&hhi.tagesaufr,&hhi.monatsaufr,&hhi.laufrtag);
 if (hhi.getcommandline()) 
	 exit(8); // Hilfe angezeigt
 if (hhi.obvi) hhi.dovi(); 
 if (hhi.obvs) exit(systemrueck("cd \""+instvz+"\"; sh viall"+devtty,/*obverb=*/0,/*oblog=*/0,/*rueck=*/0,/*obsudc=*/1));
 if (hhi.zeigvers) {
	 hhi.zeigversion();
	 Log(violetts+Txk[T_Ende]+Tx[T_zeigvers]+schwarz,hhi.obverb,hhi.oblog);
	 exit(7);
 } // if (hhi.zeigvers)
 if (!hhi.keineverarbeitung) {
	 hhi.rueckfragen();
	 hhi.pruefggfmehrfach();
	 if (hhi.logdateineu) tuloeschen(logdt,"",hhi.obverb,hhi.oblog);
	 hhi.Log(Tx[T_Logpfad]+drots+hhi.loggespfad+schwarz+Tx[T_oblog]+drot+ltoan((int)hhi.oblog)+schwarz+")");
	 if (hhi.initDB())
		 return 10;
	 hhi.pruefanrufe(hhi.My,hhi.tanrufe, hhi.obverb,hhi.oblog);
 } // 	if (!hhi.keineverarbeitung)

 hhi.pruefcron(nix); // soll vor Log(Tx[T_Verwende ... stehen
 if (!hhi.keineverarbeitung) {
	 hhi.zeigueberschrift();
	 hhi.holanr();
	 hhi.setzzaehler();
	 hhi.schreibzaehler();
 } //  if (!hhi.keineverarbeitung)

 hhi.autokonfschreib();
 hhi.update(DPROG);
 hhi.schlussanzeige();
 Log(violetts+Txk[T_Ende]+schwarz,hhi.obverb,hhi.oblog);
 return 0;
} // int main
