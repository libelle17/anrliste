#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif // _MSC_VER

#ifndef kons_H_DRIN
#define kons_H_DRIN
#ifdef _WIN32
#include <winsock2.h> // entfaellt bei mysql
#include <io.h> // fuer isatty und _isatty
#endif // _WIN32

#include <iostream> // fuer cout, cin, cerr, clog, #include <string> // string
#ifdef _MSC_VER
#include <string>
#endif // _MSC_VER

//#define obfstream
#ifdef obfstream
// #include <fstream> // fstream
#endif  // obfstream

#ifdef linux
#define vtz '/' // Verzeichnistrennzeichen
#define vtzs "/" // Verzeichnistrennzeichenstring
#elif __MINGW32__ || _MSC_VER // linux
#define vtz '\\' // Verzeichnistrennzeichen
#define vtzs "\\" // Verzeichnistrennzeichen
#endif // linux elif __MINGW32__ || _MSC_VER

#ifndef vector_incl
#include <vector> // wird in Manjaro hier nochmal extra benötigt
#define vector_incl
#endif // vector_incl
#include <sys/wait.h> // fuer waitpid

using namespace std;
extern const string& instvz; // in kons.cpp, z.B. /root/autofax
extern const string& unindt; // instvz+"uninstallinv"
extern const int sfeh[]; // T_Dienst_laeuft, T_Dienst_inexistent, ...
extern const double& versnr; // Programmversion
extern const string& spath; // PATH-Variable für root
string* loeschefarbenaus(string *zwi);
int Log(const short screen,const short file, const bool oberr,const short klobverb, const char *format, ...);
int Log(const string& text,const short screen=1,const short file=1,const bool oberr=0,const short klobverb=0);

#ifdef _MSC_VER
#define fileno _fileno // sonst Warnung posix deprecated
#define isatty _isatty // sonst Warnung posix deprecated
#endif // _MSC_VER

#ifdef __MINGW32__
#undef PATH_MAX
#endif // __MINGW32__

#ifdef _WIN32
#define PATH_MAX MAX_PATH
// #include <limits.h>
#include <time.h> // fuer mktime und time in kuerzelogdatei
#define lstat stat

#elif linux // _WIN32
#include <iomanip> // setprecision
#include <string.h> // strchr, strcpy, strtok_r, strerror, memcmp, strcmp, strstr, strlen
#include <errno.h> // errno, ENOENT
#include <pwd.h>   // getuid, getpwuid
#include <grp.h>   // getgrouplist
#include <sys/param.h>  // MAXHOSTNAMELEN
#include <sys/ioctl.h> // winsize, TIOCGWINST, w, ioctl
// #include <stdlib.h>
#include <dirent.h> // DIR, dirHandle, opendir, readdir, PATH_MAX
#include <unistd.h> // dup2, close, STDIN_FILENO, gethostname
#endif // _WIN32 elif linux

#ifndef _MSC_VER
#include <stdio.h> // fuer fopen, perror, fgets, sscanf, fputs, fclose, stdout, fileno, stderr
#else
#define snprintf _snprintf
#endif

#include <sys/stat.h> // stat, lstat, S_IFMT, S_IFDIR ...
// #include <boost/algorithm/string.hpp> // clock, numeric_limits
#include <boost/locale.hpp> // fuer to_upper und to_lower
// #include <limits>
extern const boost::locale::generator gen; // fuer to_upper, to_lower
extern const std::locale loc;

typedef unsigned char uchar; // 1 Byte
enum binaer:uchar {falsch,wahr};
enum Sprache {deutsch,englisch,SprachZahl};
extern const char *const dir;
extern const char *const tmmoegl[2];
//extern const string datei;
// extern const char *rot, *weinrot, *schwarz, *blau, *gelb; // muss spaeter kompilerunabhaengig
extern const char *const schwarz, *const dgrau, *const drot, *const rot, *const gruen, *const hgruen, *const braun, *const gelb,
			 *const blau, *const dblau, *const violett, *const hviolett, *const tuerkis, *const htuerkis, *const hgrau, *const weiss, *const umgek;
extern const string drots,rots,schwarzs,blaus,dblaus,gelbs,tuerkiss,hgraus,violetts,gruens;
#ifdef linux
extern const char *_rot, *_hrot, *_schwarz, *_blau, *_gelb, *_tuerkis, *_hgrau;
#endif // linux
#include <fstream> // kopiere
#include <algorithm>    // std::transform
#include <regex.h> // regex_t, regex, regcomp, regexec
#include <chrono> // fuer sleep_for 
#include <thread> // fuer sleep_for

#define neufind
#define altfind
#if defined(neufind) || defined(altfind)
#define mitset
#ifdef mitset
#include <set>
#else // mitset
#include <map>
#endif // mitset else
#define B_Datei 1
#define B_Verzn 2
#define B_Chdev 4
#define B_Block 8
#define B_FIFO 16
#define B_Link 32
#define B_Sock 64
#define B_Alle 127 
#define Fol_Dat 1 // folge Datei: liefere Ziel eines Links anstatt der Link-Datei
#define Fol_Ver 2 // folge Verzeichnis: suche auch in Verzeichnis, auf das ein gefundener Link zeigt, egal wo es liegt
#define Fol_Mus 4 // folge Vergleiche das Muster mit Ziel eines Links anstatt der Link-Datei
enum {
  REGFEHLER=997,
  DIRFEHLER=998, 
  REALPATHFEHLER=999
};
#endif

#define caus cout // nur zum Debuggen
#define exitt exit // fuer threads
extern pthread_mutex_t getmutex, printf_mutex, timemutex;
extern const string devtty;

typedef unsigned long long ull;
extern uchar findv/*=3*/; // find-Version 1=system, 2=intern mit readdir, 3=intern mit nftw
class elem2;
#ifdef mitset
typedef set<elem2> el2set;
#else // mitset
typedef map<elem2,ull> el2set;
#endif // mitset else
extern el2set::iterator it2;
class elem3;
extern set<elem3>::iterator it3;

extern const string nix/*=""*/;
extern const string eins/*="1"*/;
extern const string sudc/*="sudo "*/;
extern const string sudhc/*="sudo -H "*/;
// typedef const char *TCtp[][SprachZahl];
typedef const char * const * const TCtp[SprachZahl];
class TxB // Text-Basisklasse
{
 public:
  Sprache lgn; // Sprache numerisch
//  TCtp* TCp;
  const char * const * const * const *TCp;
	TxB(const char* const* const* const *TCp):TCp(TCp){}
  inline const char* operator[](long const& nr) const {
    TCtp *hilf = reinterpret_cast<TCtp*>(TCp);
    return (const char*)hilf[nr][lgn];
  }
}; // class TxB // Text-Basisklasse

string meinpfad();

enum Tkons_ 
{
	T_j_af,
  T_pfad,
  T_kuerze_logdatei,
  T_Logdatei,
  T_gibt_es_noch_nicht_Kuerze_sie_daher_nicht,
  T_Kann_Datei,
  T_nicht_als_fstream_zum_Schreiben_oeffnen,
  T_nicht_als_fstream_zum_Lesen_oeffnen,
  T_nicht_mit_fopen_zum_Schreiben_oeffnen,
  T_nicht_mit_fopen_zum_Lesen_oeffnen,
  T_Variable_logdatei_leer,
	T_Variable_logdatei_Verzeichnis,
  T_nicht_als_fstream_zum_Anhaengen_oeffnen,
	T_nicht_mit_open_zum_Anhaengen_oeffnen,
  T_nicht_mit_fopen_zum_Anhaengen_oeffnen,
  T_Bitte_mit,
  T_beenden,
  T_stern_zeile,
  T_Rueckmeldung,
  T_Suchbefehl,
  T_Fuehre_aus,
  T_fehlgeschlagen_bei,
  T_Fuehrte_aus,
  T_komma_Ergebnis,
  T_kein_Verzeichnis_nochmal,
  T_nicht_gefunden_soll_ich_es_erstellen,
  T_Fehlender_Parameter_string_zu,
  T_oder,
  T_Fehler_Parameter,
  T_ohne_gueltigen,
  T_mit_Datei_als,
  T_mit_falschem,
  T_Pfad_angegeben,
  T_Nicht_numerischer,
  T_Fehlender,
  T_Parameter_nr_zu,
  T_Fehler,
  T_Erfolg,
  T_Weder_zypper_noch_apt_get_noch_dnf_noch_yum_als_Installationspgrogramm_gefunden,
  T_Logdateidpp,
  T_Lese_Konfiguration_aus,
  T_j_k,
  T_Fehler_bei_auswert,
  T_nicht_gefunden,
  T_Muss_Datei,
  T_fuer,
  T_zugreifbar_machen,
  T_spruef_sname,
  T_lief_schon,
  T_nicht_gefunden_versuche_ihn_einzurichten,
  T_Aktiviere_Dienst,
  T_Program,
  T_laeuft_schon_einmal_Breche_ab,
  T_Wert,
  T_Dauer,
  T_Dienst,
  T_geladen,
	T_ermoeglicht,
	T_nicht_ermoeglicht,
  T_nicht_geladen,
  T_am,
  T_als_Dienst_eingerichtet_von,
  T_Versuch,
  T_machfit,
  T_Loesche_Ausrufezeichen,
  T_Fehler_beim_Loeschen,
  T_nicht_geloescht_war_eh_nicht_mehr_da,
  T_pruefpar,
  T_Konfiguration_fuer,
  T_erstellt_automatisch_durch_dieses_am,
  T_Fehler_bei_lstat,
  T_Datum_nicht_gesetzt_bei,
  T_Konnte_Datei,
  T_nicht_zum_Lesen_oeffnen,
  T_nicht_zum_Schreiben_oeffnen,
  T_Zeilen,
	T_oder_nicht,
	T_nicht_einfuegbar,
  T_erneute_Eingabe,
	T_obsfveh,
	T_laeuft_jetzt,
	T_Dienst_inexistent,
	T_Dienstdateiname_nicht_ermittelbar,
	T_Dienst_laeuft_noch_aber_Dienstdatei_inexistent,
	T_Exec_Dateiname_nicht_ermittelbar,
	T_Exec_Datei_fehlt,
	T_activating,
	T_Dienst_kann_gestartet_werden,
	T_Sonstiges,
	T_Ergebnis_Dienst,
	T_Dienst_laeuft,
	T_Dienst_disabled,
	T_stopdis_sname,
	T_enableggf,
	T_semodpruef,
	T_Exitcode,
	T_trenne,
	T_bei,
	T_Konnte_regulaeren_Ausdruck_nicht_kompilieren,
	T_doinst,
	T_Ins_Deinstallationsprogramm_wird_eingetragen,
	T_fallsnichtda,
	T_ohneabh,
	T_Tiefe,
	T_Linkverzeichnis,
	T_Suche_in,
	T_nach,
	T_Typbit,
	T_Folge,
	T_noext,
	T_Ergebnis,
	T_Fehler_beim_Deferenzieren_von,
	T_Ende,
	T_startundenable,
	T_pruefberecht,
	T_Datei,
	T_Erg,
	T_Benutzer,
	T_obunter,
	T_datei,
	T_Ergebnis_nach_make,
	T_Ergebnis_nach_make_install,
	T_Programm,
	T_Freie_Software,
	T_Verfasser,
	T_Letzte_Programmaenderung,
	T_Kompiliert,
	T_Quelle,
	T_Hilfe,
	T_Installationsverzeichnis,
	T_or,
	T_aktuelle_Einstellungen_aus,
	T_lg_k,
	T_language_l,
	T_lang_k,
	T_lingue_l,
	T_sprachstr,
	T_v_k,
	T_verbose_l,
	T_lvz_k,
	T_logvz_l,
	T_ld_k,
	T_logdname_l,
	T_l_k,
	T_log_l,
	T_ldn_k,
	T_logdateineu_l,
	T_kd_k,
	T_konfdatei_l,
	T_Bildschirmausgabe_gespraechiger,
	T_waehlt_als_Logverzeichnis_pfad_derzeit,
	T_logdatei_string_im_Pfad,
	T_sonst_knapper,
	T_wird_verwendet_anstatt,
	T_logdatei_vorher_loeschen,
	T_verwendet_Konfigurationsdatei_string_anstatt,
	T_standardhilfe,
	T_libtest,
	T_protokolliert_ausfuehrlich_in_Datei,
	T_sh,
	T_lieskonfein,
	T_pruefcron,
	T_cronzuplanen,
	T_Kein_cron_gesetzt_nicht_zu_setzen,
	T_wird,
	T_unveraendert,
	T_alle,
	T_Minuten,
	T_gar_nicht,
	T_aufgerufen,
	T_statt,
	T_schlussanzeige,
	T_Zeit_Doppelpunkt,
	T_Fertig_mit,
	T_eigene,
	T_entfernen,
	T_belassen,
	T_warte,
	T_wird_aktualisiert_bitte_ggf_neu_starten,
	T_muss_nicht_aktualisiert_werden,
	T_confdat_lies_Datei,
	T_confdat_lies_Erfolg,
	T_confdat_lies_Misserfolg,
	T_pruefsamba,
	T_Samba_muesste_installiert_werden_soll_ich,
	T_Sollen_fehlende_Sambafreigaben_fuer_die_angegebenen_Verzeichnisse_ergaenzt_werden,
	T_Passwort_fuer_samba,
	T_Firewallport,
	T_offen,
	T_zu,
	T_Soll_die_SuSEfirewall_bearbeitet_werden,
	T_Verzeichnis,
	T_nicht_als_Sambafreigabe_gefunden_wird_ergaenzt_in,
	T_fuer_Benutzer,
	T_prueftif,
	T_holsystemsprache,
	T_hcl_hcl,
	T_erfolgreich_fuer,
	T_Libtiff_Version,
	T_Fertig_mit_Parsen_der_Befehlszeile,
	T_ja,
	T_nein,
	T_Testaufruf_wegen_Programmbibliotheken,
	T_Gebrauch,
	T_Optionen_die_nicht_gespeichert_werden,
	T_Optionen_die_in_der_Konfigurationsdatei_gespeichert_werden,
	T_konsMAX
}; // Tkons_

extern const string sprachstr;
/*
extern class Txkonscl Txk;

class Txkonscl : public TxB
{
  public:
    static const char *TextC[T_konsMAX+1][SprachZahl];
    Txkonscl();
//    inline const char* operator[](Tkons_ const& nr) const { return TextC[nr][lgn]; }
};
*/
extern class TxB Txk;

extern uchar nrzf; // nicht rueckzufragen, fuer Aufruf aus Cron

class errmsgcl
{
public:
 int errnr;
 string msg;
 errmsgcl(int errnr,const string& msg):errnr(errnr),msg(msg){}
};
// aktueller Benutzer
class cuscl
{
 private:
 struct passwd *passwd;
 public:
 string cusstr;
 uid_t cuid;
 gid_t cgid;
 cuscl();
};

// arg-Class
class argcl
{
 public:
 const char *argcs;  // Zeiger auf einen Commandline-Parameter
 uchar agef=0; // dieser wurde gefunden
 argcl(const int i, const char *const *const argv);
};

class perfcl
{
 public:
 string vonwo;
 clock_t zp0, zp1, zp1alt;
 time_t t0=0, t1;
 unsigned long nr=0;
 perfcl(const string& vvonwo);
 void ausgeb(const string& stelle=nix,uchar obdauer=0);
 void ausgab1000(const string& stelle=nix);
 int oberreicht(unsigned long sek);
};

string holsystemsprache(int obverb=0);
int pruefberecht(const string& datei,const string& benutzer,const mode_t mod=01,int obverb=0);
int untersuser(const string& uname,__uid_t *uidp=0, __gid_t *gidp=0, vector<gid_t> *gids=0,struct passwd* ustr=0);
double verszuzahl(const string& vers);

class mdatei: public fstream
{
  public:
  int oboffen=0;
  mdatei(const string& filename, ios_base::openmode mode=ios_base::in|ios_base::out, uchar faclbak=1, int obverb=0, int oblog=0);
}; // class mdatei: public fstream

// Zeitausgabeklasse, um time_t-Variablen formatiert in ostream-Objekte ausgeben zu koennen, z.B. <<ztacl(zt,"%F %T")<<
class ztacl {
	private:
		const time_t zt;
		const char* fmt;
	public:
		explicit ztacl(time_t &pzt,const char* pfmt):zt(pzt),fmt(pfmt) {
		}
		std::ostream &operator()(std::ostream& out) const;
}; // ztacl
ostream &operator<<(ostream &out,ztacl ztaus);

inline string zustr(int _Val) 
{
  char _Buf[2 * sizeof(long long)];
  snprintf(_Buf,2*sizeof(long long), "%d", _Val);
  return string(_Buf);
} // inline string zustr(int _Val)

inline std::string right(std::string const& source, size_t const length)
{
  if (length >= source.size()) { return source; }
  return source.substr(source.size() - length);
} // inline std::string right(std::string const& source, size_t const length)

inline std::string mitvtz(std::string const& vz)
{
  if (right(vz,1)==string(1,vtz)) {
    return vz;
  } else {
    return vz+vtz;
  }
} // inline std::string mitvtz(std::string const& vz)

inline int istelnr(const std::string& str)
{
  if	(str.find_first_not_of("+ 0123456789.,")==string::npos && str.find_first_not_of(" ")!=string::npos) 
    return 1;
  return 0;
} // inline int istelnr(const std::string& str)

inline int isnumeric(const std::string& str)
{
  if	(str.find_first_not_of(" 0123456789.,")==string::npos && str.find_first_not_of(" ")!=string::npos) 
    return 1;
  return 0;
} // inline int isnumeric(const std::string& str)

inline int isneun(const std::string& str)
{
  if	(str.find_first_not_of(" 9")==string::npos && str.find_first_not_of(" ")!=string::npos) 
    return 1;
  return 0;
} // inline int isneun(const std::string& str)


inline int isnumeric(const char* str)
{
  while (*str) {
    if(!strchr(" 0123456789.,",*str)) return 0;
    str++;
  }
  return 1;
} // inline int isnumeric(char* str)
 
string* anfzweg(string& quel);
char ers(const char roh);

// Gesamt-Trim
inline std::string *gtrim(std::string *str) {
  str->erase(0, str->find_first_not_of("\t "));       //prefixing spaces
  str->erase(str->find_last_not_of("\t ")+1);         //surfixing spaces
  return str;
} // inline std::string *gtrim(std::string *str)

inline std::string *ltrim(std::string *str) {
  str->erase(0, str->find_first_not_of("\t "));       //prefixing spaces
  return str;
} // inline std::string *ltrim(std::string *str)

inline void rtrim(char* str,size_t size) {
  for (int nd=0,i=size-1;i;i--) {
    if (!str[i]) nd=1; 
    else if (nd && str[i]!=32 && str[i]!=9) break;
    str[i]=0;
  } //   for (int nd=0,i=size-1;i;i--)
} // inline void rtrim(char* str,size_t size)

string fersetze(const string& u, const char* alt, const char* neu);
string caseersetze(const string& u, const char* const alt, const char* const neu); 
string *loeschealleaus(string *u, const char* alt);

string ersetze(const char *const u, const char* const alt, const char* const neu);
string *sersetze(string *src, string const& target, string const& repl);
// wstring ersetze(const wstring& u, const wchar_t* alt, const wchar_t* neu); 
string nersetze(const string& quelle,string was, string durch);

string ersetzAllezu(const string& quelle, const string& alt, const string& neu);
void ersetzAlle(string& quelle, const string& alt, const string& neu);
string ersetzAllezu(string *quelle, const char* const alt, const char* const neu);
string ersetzAllezu(const char *const quelle, const char* const alt, const char* const neu);
void ersetzAlle(string *quelle, const char* const alt, const char* const neu);
void ersetzAlle(string *quelle, const string& alt, const string& neu);

char* charersetze(char *u, const char alt, const char neu);
void chersetze(const string& u, string *z, const string& alt, const char neu);
string ersetzefuerdatei(const string& u);
void fuersamba(string& roh);
size_t zahlin(const string *const str, const char* const was);
long cmpmem( char* feld, const char* search, int len_feld); // , int len_search
// fuer lies (Konfigurationsdatei lesen)
string ltoan(long value, int base=10, uchar obtz=0, uchar minstel=0); 
char* ltoa_(long value, char* result, int base); 
void anfgw(const string& datei, const string& udpr, const string& inhalt, const string& comment, int obverb/*=0*/, int oblog/*=0*/);
void anfgg(const string& datei, const string& inhalt, const string& comment, int obverb/*=0*/, int oblog/*=0*/);
void doanfg(const string& datei, const string& inhalt, const string& comment);

int touch(const std::string& pathname,int obverb=0,int oblog=0);
std::string string_to_hex(const std::string& input);
int dateivgl(const string& d1, const string& d2,uchar obzeit=0);
void kuerzevtz(string *vzp);

#ifdef notcpp
class Schluessel {
  public:
    char key[90];
    char val[100];
    template <typename T> void hole(T *var) { *var=atol(val); }
    template <typename T> void setze(T *var) { strncpy(val,ltoan(*var),sizeof val-1);val[sizeof val-1]=0; }
};
template <> inline void Schluessel::hole < char* > (char** var) { *var = val; }
template <> inline void Schluessel::hole < const char* > (const char** var) { *var = val; }
template <> inline void Schluessel::hole < string > (string *var) { *var = val; }
template <> inline void Schluessel::hole < binaer > (binaer *var) { *var = (binaer)atoi(val); }
template <> inline void Schluessel::setze < char* > (char** var) { strncpy(val,*var,sizeof val-1);val[sizeof val-1]=0; }
template <> inline void Schluessel::setze < const char* > (const char** var) { strncpy(val,*var,sizeof val-1);val[sizeof val-1]=0; }
template <> inline void Schluessel::setze < string > (string *var) { strncpy(val,var->c_str(),sizeof val-1);val[sizeof val-1]=0;}
#endif // notcpp

class cppSchluess {
  public:
    string name;
    uchar gelesen=0;
    string wert;
    string bemerk;
//    inline cppSchluess& operator=(cppSchluess zuzuw){name=zuzuw.name;wert=zuzuw.wert; return *this;} // wird nicht benoetigt
    template <typename T> void hole(T *var) { *var=atol(wert.c_str()); }
    template <typename T> void setze(T *var) { wert=ltoan(*var); }
//    template <typename T> void setze(T *var,string& bem) { wert=ltoan(*var); bemerk=bem;}
		void hole (struct tm *tmp);
}; // class cppSchluess
template <> inline void cppSchluess::hole < char* > (char** var) {*var = (char*)wert.c_str(); }
template <> inline void cppSchluess::hole < const char* > (const char** var) {*var = wert.c_str(); }
template <> inline void cppSchluess::hole < string > (string *var) {*var = wert; }
template <> inline void cppSchluess::hole < binaer > (binaer *var) { *var = (binaer)atoi(wert.c_str()); }
/*
template <> inline void cppSchluess::hole < struct tm > (struct tm *tmp) {
	if (!wert.empty()) {
		for(unsigned im=0;im<sizeof tmmoegl/sizeof *tmmoegl;im++) {
			if (strptime(wert.c_str(), tmmoegl[im], tmp)) break;
		}
									//		strptime(wert.c_str(), "%d.%m.%y %T", tmp);
	}
}
*/
template <> inline void cppSchluess::setze < char* > (char** var) {wert=*var;  }
template <> inline void cppSchluess::setze < const char* > (const char** var) {wert=*var; }
template <> inline void cppSchluess::setze < string > (string *var) {wert=*var;}
template <> inline void cppSchluess::setze < const string > (const string *var) {wert=*var; }
template <> inline void cppSchluess::setze < struct tm > (struct tm *tmp) {
	char buf[30];
	strftime(buf, sizeof(buf), "%d.%m.%y %T", tmp);
	wert=buf;
}
/*
template <> inline void cppSchluess::setze < char* > (char** var, string& bem) {wert=*var; if (!bem.empty()) bemerk=bem; }
template <> inline void cppSchluess::setze < const char* > (const char** var, string& bem) {wert=*var; if (!bem.empty()) bemerk=bem;}
template <> inline void cppSchluess::setze < string > (string *var, string& bem) {wert=*var;if (!bem.empty()) bemerk=bem;}
template <> inline void cppSchluess::setze < const string > (const string *var, string& bem) {wert=*var; if (!bem.empty()) bemerk=bem;}
*/
class svec;

class schlArr {
 public:
 cppSchluess *schl=0; 
 size_t zahl;
 schlArr();
 schlArr(const char* const* sarr,size_t vzahl);
 void neu(size_t vzahl=0);
 void init(size_t vzahl, ...);
 void init(vector<cppSchluess*> *sqlvp);
 void initd(const char* const* sarr,size_t vzahl);
 inline /*const*/ cppSchluess& operator[](size_t const& nr) const { return schl[nr]; }
 int setze(const string& name, const string& wert/*, const string& bem=nix*/);
 const string& hole(const string& name);
 void setzbemv(const string& name,TxB *TxBp,size_t Tind,uchar obfarbe=0,svec *fertige=0);
 void aschreib(mdatei *const f);
 int fschreib(const string& fname);
 void ausgeb();
 void reset();
 ~schlArr();
}; // class schlArr

class abSchl {
 public:
   string name;
   string wert;
   abSchl(string& vname, string& vwert):name(vname),wert(vwert) {}
}; // class abSchl

// Linux-System-Enum
enum lsysen:uchar {usys,sus,deb,fed};
class lsyscl
{
    lsysen sys=usys; 
		string usr_lib64_vz;
  public:
    lsysen getsys(int obverb=0,int oblog=0);
		string& getlib64(int obverb=0,int oblog=0);
}; // class lsyscl

// enum betrsys {keins,suse,ubuntu,fedora};
// betrsys pruefos();
int obprogda(const string& prog, int obverb=0, int oblog=0, string *pfad=0);
enum instprog {keinp,zypper,apt,dnf,yum,urp,pac};
string gethome();


#ifdef _MSC_VER
extern inline void wait();
#else // _MSC_VER
// #define wait();
#endif // _MSC_VER

#ifdef _WIN32
extern const char *drot, *rot, *schwarz, *blau, *gelb, *tuerkis, *hgrau;
extern const string drots, rots, schwarzs, blaus, gelbs, tuerkis, hgrau;
inline std::ostream& _drot(std::ostream &s){
  //    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_INTENSITY);
  return s;
}
inline std::ostream& _blau(std::ostream &s){
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE|FOREGROUND_INTENSITY);
  return s;
}
inline std::ostream& _rot(std::ostream &s){
  //    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
  return s;
}
inline std::ostream& _schwarz(std::ostream &s){
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
  return s;
}
inline std::ostream& _gelb(std::ostream &s){
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN);
  return s;
}
struct color {
  color(WORD attribute):m_color(attribute){};
  WORD m_color;
};

#endif // _WIN32
class svec: public vector<std::string>
{
  public:
    inline svec& operator<<(const std::string& str) {
      this->push_back(str);
      return *this;
    }
}; // class svec: public vector<std::string>

//svec& operator<<(svec& v, const std::string& str);
template<class T>
class tsvec: public vector<T>
{
  public:
    inline tsvec<T>& operator<<(const T& str) {
      this->push_back(str);
      ((T&)str).init();
      return *this;
    } // inline tsvec
}; // template<class T> class tsvec: public vector<T>


// Abschnitt einer Konfigurationsdatei
class absch
{
 public:
 string aname;
 vector<abSchl> av;
 const string& suche(const char* const sname);
 const string& suche(const string& sname);
 void clear();
}; // class absch

class confdat
{
  private:
  public:
    uchar obgelesen=0;
    svec zn;
    string name;
    vector<absch> abschv;
    size_t richtige;
    confdat(const string& fname, int obverb);
    confdat(const string& fname, schlArr *sA, int obverb=0, const char tz='=');
		confdat();
		void init(const string& fname, schlArr *sA, int obverb=0, const char tz='=');
////    confdat(const string& fname,cppSchluess *conf, size_t csize, int obverb=0, char tz='=');
    int lies(const string& fname,int obverb);
    void auswert(schlArr *sA, int obverb=0, const char tz='=');
////    void auswert(cppSchluess *conf, size_t csize, int obverb=0, char tz='=');
    void Abschn_auswert(int obverb=0, const char tz='=');
}; // class confdat

// fuer Commandline-Optionen
enum par_t:uchar {psons,pverz,pfile,pzahl}; // Parameterart: Sonstiges, Verzeichnis, Zahl


class optioncl
{
  public:
//    const string kurz;
//    const string lang;
		const int kurzi=0;
		const int langi=0;
    TxB *TxBp=0;
    const long Txi=0;
		uchar wi=0; // Wichtigkeit: 1= wird mit -lh oder -h, 0= nur mit -lh, 255 (-1) = gar nicht angezeigt
    const string *rottxt=0; // ggf rot zu markierender Text zwischen Txi und Txi2
    long Txi2=-1;
//    string oerkl;
    uchar *pptr=0; // Zeiger auf binären Parameter, der hier eingestellt werden kann
    int wert; // Wert, der pptr zugewiesen wird, falls dieser Parameter gewaehlt wird
    string *zptr=0; // Zeiger auf Zusatzparameter, der hier eingegeben werden kann (z.B. Zahl der Zeilen nach -n (Zeilenzahl)
    const par_t art; // Parameterart
    schlArr *cpA=0; // Konfigurationsarray, das ggf. geschrieben werden muss
    const char *pname; // Name des Konfigurationsparameters
    uchar *obschreibp=0; // ob Konfiguration geschrieben werden muss
//    uchar ogefunden=0; // braucht man nicht, ist in argcl
    const uchar obno=0; // ob auch die Option mit vorangestelltem 'no' eingefueft werden soll
    string bemerkung;
		uchar obcl=0; // ob die Option ueber die Kommandozeile gesetzt wurde
  private:
    void setzebem(schlArr *cpA,const char *pname);
  public:
///*1*/optioncl(string kurz,string lang,TxB *TxBp,long Txi,uchar wi) : 
//               kurz(kurz),lang(lang),TxBp(TxBp),Txi(Txi),wi(wi) {}
// /*2*/optioncl(string kurz,string lang,TxB *TxBp,long Txi,uchar wi,string *zptr,par_t art,schlArr *cpA=0,const char *pname=0,uchar* obschreibp=0);
/*2a*/optioncl(int kurzi,int langi,TxB *TxBp,long Txi,uchar wi,string *zptr,par_t art,schlArr *cpA=0,const char *pname=0,uchar* obschreibp=0);
// /*3*/optioncl(string kurz,string lang,TxB *TxBp,long Txi,uchar wi,const string *rottxt,long Txi2,string *zptr,par_t art,schlArr *cpA=0, const char *pname=0,uchar* obschreibp=0);
/*3a*/optioncl(int kurzi,int langi,TxB *TxBp,long Txi,uchar wi,const string *rottxt,long Txi2,string *zptr,par_t art,schlArr *cpA=0,
              const char *pname=0,uchar* obschreibp=0);
/*3b*/optioncl(int kurzi,int langi,TxB *TxBp,long Txi,uchar wi,const string *rottxt,long Txi2,int *pptr,par_t art,schlArr *cpA=0,
              const char *pname=0,uchar* obschreibp=0);
// /*4a*/optioncl(string kurz,string lang,TxB *TxBp,long Txi,uchar wi,uchar *pptr,int wert,schlArr *cpA=0,const char *pname=0,uchar* obschreibp=0);
/*4*/optioncl(int kurzi,int langi,TxB *TxBp,long Txi,uchar wi,uchar *pptr,int wert,schlArr *cpA=0,const char *pname=0,uchar* obschreibp=0);
///*5*/optioncl(string kurz,string lang,TxB *TxBp,long Txi,uchar wi,string *rottxt,long Txi2,uchar *pptr,int wert) : 
//               kurz(kurz),lang(lang),TxBp(TxBp),Txi(Txi),wi(wi),rottxt(rottxt),Txi2(Txi2),pptr(pptr),wert(wert) {}
// /*6*/optioncl(string kurz,string lang,TxB *TxBp,long Txi,uchar wi,const string *rottxt,long Txi2,uchar *pptr,int wert) : kurz(kurz),lang(lang),TxBp(TxBp),Txi(Txi),wi(wi),rottxt((string*)rottxt),Txi2(Txi2),pptr(pptr),wert(wert) {}
/*6a*/optioncl(int kurzi,int langi,TxB *TxBp,long Txi,uchar wi,const string *rottxt,long Txi2,uchar *pptr,int wert) : 
               kurzi(kurzi),langi(langi),TxBp(TxBp),Txi(Txi),wi(wi),rottxt((string*)rottxt),Txi2(Txi2),pptr(pptr),wert(wert),art(psons) {}
///*7*/optioncl(string kurz,string lang,TxB *TxBp,long Txi,uchar wi,binaer *pptr,int wert) : 
//               kurz(kurz),lang(lang),TxBp(TxBp),Txi(Txi),wi(wi),pptr((uchar*)pptr),wert(wert) {}
///*8*/optioncl(string kurz,string lang,TxB *TxBp,long Txi,uchar wi,int *pptr,int wert) : 
//               kurz(kurz),lang(lang),TxBp(TxBp),Txi(Txi),wi(wi),pptr((uchar*)pptr),wert(wert) {}
// /*9*/optioncl(string kurz,string lang,TxB *TxBp,long Txi,uchar wi,string *rottxt,long Txi2,int *pptr,int wert) : kurz(kurz),lang(lang),TxBp(TxBp),Txi(Txi),wi(wi),rottxt(rottxt),Txi2(Txi2),pptr((uchar*)pptr),wert(wert) {}
/*9a*/optioncl(int kurzi,int langi,TxB *TxBp,long Txi,uchar wi,string *rottxt,long Txi2,int *pptr,int wert) : 
               kurzi(kurzi),langi(langi),TxBp(TxBp),Txi(Txi),wi(wi),rottxt(rottxt),Txi2(Txi2),pptr((uchar*)pptr),wert(wert),art(psons) {}
    int pruefpar(vector<argcl> *const argcvm , size_t *const akt, uchar *hilfe, Sprache lg); // 1 = das war der Parameter, 0 = nicht
    string& machbemerkung(Sprache lg,binaer obfarbe=wahr);
    void hilfezeile(Sprache lg);
}; // class optioncl

#endif // kons_H_DRIN

extern const char *logdt;

int kuerzelogdatei(const char* logdatei,int obverb);

// #define notwendig
#ifdef notwendig
void kopierm(const string *quelle, const string *ziel);
#endif // notwendig
void aufSplit(vector<string> *tokens, const char* const text, const char sep=' ',bool auchleer=1);
void aufSplit(vector<string> *tokens, const string& text, const char sep=' ',bool auchleer=1);
void aufiSplit(vector<string> *tokens, const string& text, const string& sep,bool nichtmehrfach=1,int obverb=0,int oblog=0);
void aufSplit(vector<string> *tokens, const string& text, const char* const sep, bool auchleer=1);
size_t irfind(const string& wo, const string& was); // suche von hinten und ignoriere Gross- und Kleinschreibung
void getstammext(const string *const ganz, string *stamm, string *exten);
// int cpplies(string fname,cppSchluess *conf,size_t csize,vector<string> *rest=0,char tz='=',short obverb=0);
string XOR(const string& value, const string& key);
#ifdef notcpp
int Schschreib(const char *fname, Schluessel *conf, size_t csize);
#endif // notcpp
int cppschreib(const string& fname, cppSchluess *conf, size_t csize);
// int multicppschreib(const string& fname, cppSchluess **conf, size_t *csizes, size_t cszahl);
int multischlschreib(const string& fname, schlArr *const *const confs, const size_t cszahl,const string& mpfad=nix);
std::string base_name(const std::string& path); // Dateiname ohne Pfad
std::string dir_name(const std::string& path);  // Pfadname einer Datei
int systemrueck(const string& cmd, char obverb=0, int oblog=0, vector<string> *rueck=0, const uchar obsudc=0,
                const int verbergen=0, int obergebnisanzeig=wahr, const string& ueberschr=nix,vector<errmsgcl> *errm=0,uchar obincron=0,
								stringstream *ausgp=0,uchar obdirekt=0);
void pruefplatte();
void pruefmehrfach(const string& wen=nix,uchar obstumm=0);
void setfaclggf(const string& datei,int obverb=0,int oblog=0,const binaer obunter=falsch,int mod=4,uchar obimmer=0,
                uchar faclbak=0,const string& user=nix,uchar fake=0,stringstream *ausgp=0);
int pruefverz(const string& verz,int obverb=0,int oblog=0, uchar obmitfacl=0, uchar obmitcon=0,
              const string& besitzer=nix, const string& benutzer=nix, const uchar obmachen=1);
string aktprogverz();
char Tippbuchst(const string& frage, const string& moegl,const char *berkl[], const char* erlaubt=0, const char *vorgabe=0);
// vorgabe fur vorgabe = T_j_k; alternativ='n'
uchar Tippob(const string& frage,const char *vorgabe=Txk[T_j_k]);
string Tippstrs(const char *frage, char* moegl[], char *vorgabe=0); // das letzte Element von moegl muss 0 sein
string Tippstrs(const char *frage, vector<string> *moegl, string *vorgabe=0); 
string Tippzahl(const char *frage, const char *vorgabe=0);
string Tippzahl(const char *frage, const string *vorgabe);
string Tippzahl(const string& frage, const string *vorgabe);
long Tippzahl(const string& frage,const long& vorgabe);
string Tippstr(const char *frage, const string *vorgabe=0,const uchar obnichtleer=1);
// char* Tippcstr(const char *frage, char* buf, unsigned long buflen, const char* vorgabe=nix);
string Tippstr(const string& frage, const string *vorgabe=0,const uchar obnichtleer=1);
string Tippverz(const char *frage,const string *vorgabe=0);
uchar VerzeichnisGibts(const char* vname);
int tuloeschen(const string& zuloe,const string& cuser=nix,int obverb=0, int oblog=0,stringstream *ausgp=0);
int attrangleich(const string& zu, const string& gemaess,const string* const zeitvondtp=0, int obverb=0, int oblog=0);
int kopier(const string& quel, const string& ziel, int obverb=0, int oblog=0);
#ifdef falsch
#define obfstream
#ifdef obfstream
fstream*
#else // obfstream
FILE*
#endif // obfstream else
oeffne(const string& datei, uchar art, uchar* erfolg,uchar faclbak=1,int obverb=0, int oblog=0);
#endif // falsch

class linst_cl
{
 public:
 instprog ipr=keinp; // installiertes Program
 string schau; // Befehl zum Pruefen auf Vorhandensein ueber das Installationssystem
 string instp; // Befehl zum Installieren ueber das Installationnssystem
 string instyp; // Befehl zum Installieren ueber das Installationnssystem mit automatischem yes auf Rueckfragen
 string upr;   // Befehl zum Deinstallieren ueber das Installationssystem
 string udpr;   // Befehl zum direkten Deinstallieren
 string uypr;   // Befehl zum Deinstallieren ueber das Installationssystem ohne Rueckfrage
 string upd;    // Befehl zum Systemupdate
 string repos; // Befehl zum Hinzufuegen des Repositories fuer den Compiler
 string compil; // Paketnamen fuer den Compiler
 string dev; // Anhaengsel fuer die development-Versionen ("-dev" oder "-devel")
 string libs; // alle lib-Verzeichnisse, fuer find ..
 string shpf; // Pfad zu sh
 string xargspf; // Pfad zu xargs
 string ionicepf; // Pfad zu ionice
 string nicepf; // Pfad zu nice
 string p3cpf; // Pfad zu python3-config

 linst_cl(int obverb=0, int oblog=0);
 uchar obnmr=1;
 string eprog; // ersetztes Programm
 const string ersetzeprog(const string& prog) const;
 void ziehraus(svec srueck, string* ustringp);
 int doinst(const string& prog,int obverb=0,int oblog=0,const string& fallsnichtda=nix,uchar ohneabh=0);// ,uchar obyes=1);
 int doggfinst(const string& prog,int obverb=0,int oblog=0,uchar ohneabh=0);
 int douninst(const string& prog,int obverb=0,int oblog=0,uchar obyes=1);
 int obfehlt(const string& prog,int obverb=0,int oblog=0);
}; // class linst_cl

// Service aus SystemD
class servc {
  public:
		string systemd; // Dienst-Datei
    int svfeh=-1; // Ausgangseinstellung
		int svf0=-1; // Einstellung nach erstem Ablauf von obsvfeh
		int obenabled=0;
	// svfeh=1: Dienst inexistent, 2: Dienst 'disabled' 3: Dienstdatei nicht ermittelbar, 4: Dienst laeuft noch, aber Dienstdatei inexistent
	// svfeh=5: Exe-Datei nicht ermittelbar, 6: Exe-Datei fehlt, 7: activating 8: Dienst kann gestartet werden, 9: Sonstiges
    int fehler=0; // Exit-Code der Exe-Datei
    string sname,ename; // Dienstname, Exename
    servc(const string& vsname,const string& vename): sname((vsname.empty()?vename:vsname)),ename(vename) {}
    servc(const string& vsname,const string& vename,int obverb, int oblog);
    // int obda(int obverb,int oblog);
		int startbar();
		int laeuft();
		int lief();
		int obsvfeh(int obverb=0,int oblog=0); // ob service einrichtungs fehler
		uchar spruef(const string& sbez,uchar obfork,const string& parent, const string& sexec, const string& CondPath, const string& After, 
                 linst_cl *linstp, int obverb=0,int oblog=0, uchar mitstarten=1);
    int restart(int obverb=0, int oblog=0);
    void start(int obverb=0, int oblog=0);
    int startundenable(int obverb=0, int oblog=0);
    void stop(int obverb=0,int oblog=0,uchar mitpkill=0);
		void stopggf(int obverb=0,int oblog=0,uchar mitpkill=0);
		void stopdis(int obverb=0,int oblog=0,uchar mitpkill=0);
    void pkill(int obverb=0,int oblog=0);
    int enableggf(int obverb=0,int oblog=0);
    int machfit(int obverb=0, int oblog=0, binaer nureinmal=falsch);
		void semodpruef(linst_cl *linstp,int obverb=0,int oblog=0);
		void semanpruef(int obverb=0,int oblog=0,const string& mod="getty_t");
		static void daemon_reload(int obverb=0, int oblog=0);
};

void printBits(size_t const size, void const * const ptr); // Binaerausgabe, fuer Debugging

#ifdef altfind
class elem2
{
  public:
    string pfad;
    struct stat dst={0};
    int sterg;
    elem2(){};
    elem2(const string& mutter,const string& name);
    void init(const string& vmutter, const string& name);
    const bool operator<(const elem2& el) const;
}; // class elem2

class find2cl: elem2
{
  string typ;
  vector<string> stack;
  DIR *dir;
  struct dirent *dent;
  public:
  el2set *ergp=0;
  set<string> *vznp=0; 
  ull *nrp=0;
  int zuloeschen=1;
  int eingefuegt, verzneu;
	int obverb,oblog;
	find2cl(int _obverb=0, int _oblog=0, find2cl *stamm=0);
  ~find2cl();
  void weiszu();
  void init(const string& mutter, const string& name, regex_t *reg, const int folge,const long maxdepth, const int& typbit,
      vector<string> stack,time_t ab, time_t bis,int nurexec);
  void ausgeb();
  int finde(svec *wovp, const string& muster=nix,const long tiefe=-1,int typbit=B_Alle,int folge=Fol_Dat,
	          time_t ab=0, time_t bis=0,int obicase=0,int nurexec=0,int obnoext=0);
	void zuvec(svec *zu,uchar anteil=0);
};
#endif // altfind

#ifdef neufind
#include <ftw.h>
// Fundelement
class elem3
{
  public:
    string pfad;
    const struct stat sb={0};
    int tflag;
    const struct FTW ftw={0};
    const string lnk;
    const struct stat lst={0};
    elem3(string pfad, const struct stat *sbp, int& tflag, const struct FTW *ftwp, string lnk,const struct stat& lst):
          pfad(pfad),sb(*sbp),tflag(tflag),ftw(*ftwp),lnk(lnk),lst(lst){}
    const bool operator<(const elem3& el) const;
};

// Wurzelelement
class wele
{
  public:
    const string pfad;
    const long maxd;
    wele(const string& pfad=nix, const long& maxd=-1):pfad(pfad),maxd(maxd){}
    const bool operator<(const wele& el) const;
//    bool operator()(const wele& el3) const {return (this->pfad<el3.pf);}
}; // class wele

// nur eine Instanz der Klasse kann gleichzeitig gefuellt werden wegen der statischen Elemente
class find3cl
{
  public:
    int flags = 0;
    long maxdepth=-1;
    static long *maxdepthp;
    int folge=0;
    static int *folgep;
    set<wele> wurz,fertige;
    set<elem3> erg;
    static set<wele>::iterator it;
    static set<wele> *wurzp;
    static set<elem3> *ergp;
    regex_t reg;
    static regex_t *regp;
    int typbit;
    static int *typbitp;
    time_t mab,mbis;
    static time_t *mabp,*mbisp;
		int obverb=0, oblog=0;
		static int *obverbp, *oblogp;
		int nurexec;
		static int *nurexecp;
		find3cl(int obverb=0,int oblog=0);
    static int verarbeit(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf);
    int dofind();
    int ausgeb();
    int finde(svec *wovp,const string& muster=nix,long tiefe=-1,int _typbit=B_Alle,int _folge=Fol_Dat,
		           time_t _mab=0,time_t _mbis=0,int obicase=0,int nurexec=0,int obnoext=0);
		void zuvec(svec *zu,uchar anteil=0);
}; // class find3cl
#endif // neufind
#if defined(altfind) && defined(neufind)
void findfile(svec *qrueck,uchar findv,int obverb=0,int oblog=0,uchar anteil=0,
		const string& wo=".",const string& muster=nix,long tiefe=-1,int _typbit=B_Alle,int _folge=Fol_Dat, 
		time_t _mab=0,time_t _mbis=0,int obicase=0,int nurexec=0,int obnoext=0,uchar nureins=0);
#endif

class pidcl
{
 public:
 pid_t pid;
 string name;
 pidcl(const pid_t pid,const string& name):pid(pid),name(name){}
}; // pidcl

//Vector von pid- und string-Pärchen
class pidvec: public vector<pidcl>
{
 public:
 inline pidvec& operator<<(const pidcl& pd) {
	 this->push_back(pd);
	 return *this;
 } //  inline pidvec& operator<<(const pidcl& pd)
}; // pidvec

int wartaufpids(pidvec *pidv,const ulong runden=0,const int obverb=0,const int oblog=0,const string& wo=nix);

extern const string s_true; // ="true";
extern const string s_dampand; // =" && ";
extern const string s_gz; // ="gz";
extern const string& defvors; // ="https://github.com/"+gitv+"/";
extern const string& defnachs; // ="/archive/master.tar.gz";
void viadd(string *cmd,const string& datei,const uchar ro=0,const uchar hinten=0, const uchar unten=0);

// Haupt-Klasse
class hcl
{
	protected:
    double tstart, tende;
    size_t optslsz=0; // last opts.size()
		unsigned lfd;
    uchar rzf=0; // rueckzufragen
		confdat afcd;
		string tmpcron; // fuer crontab
    string cronminut; // Minuten fuer crontab; 0 = kein Crontab-Eintrag
		uchar nochkeincron;
		uchar cronzuplanen;
		uchar cmeingegeben=0; // cron-Minuten eingegeben
		uchar crongeprueft=0;
		static const string edit;
		static const string passwddt, groupdt, sudoersdt;
		static const char* const smbdt;// "/etc/samba/smb.conf"
		uchar autoupd;  // 1=Programm automatisch updadaten
	public:
    int obverb=0; // verbose
    int oblog=0;  // mehr Protokollieren
    string langu; // Sprache (Anfangsbuchstabe)
    string logdname; // Logdatei-Name ohne Pfad <DPROG>.log
    string logvz; // nur das Verzeichnis /var/log
    string loggespfad; // Gesamtpfad, auf den dann die in kons.h verwiesene und oben definierte Variable logdt zeigt
                       // bei jeder Aenderung muss auch logdt neu gesetzt werden!
    string cmd; // string fuer command fuer Betriebssystembefehle
    vector<optioncl> opts;
		vector<argcl> argcmv; // class member vector
		ulong aufrufe=0; // Zahl der bisherigen Programmaufrufe
		struct tm laufrtag={0}; // Tag des letztes Aufrufs
		ulong tagesaufr=0; // Zahl der bisherigen Programmaufrufe heute
		ulong monatsaufr=0; // Zahl der bisherigen Programmaufrufe heute
    uchar oblgschreib=0; // Konfigurationsdatei seitens der Sprache voraussichtlich schreiben
    uchar obkschreib=0; // Konfigurationsdatei schreiben
    uchar logdneu=0;    // Logdatei geaendert
    uchar logvneu=0;    // Logverzeichnis geaendert
    uchar logdateineu=0; // logdt vorher loeschen
    uchar obhilfe=0;      // Hilfe anzeigen: 1=kurze Hilfe, 2=lange Hilfe, 3=Standardhilfe
    uchar zeigvers=0;  // Version anzeigen
		string cl; // comandline
    string mpfad;  // meinpfad()
    string meinname; // base_name(meinpfad()) // argv[0] // <DPROG>
    string akonfdt; // name der Konfigurationsdatei
    schlArr agcnfA; // Gesamtkonfiguration
		string azaehlerdt; // akonfdt+".zaehl"
		schlArr zcnfA; // Zaehlkonfiguration
		string vorcm; // Vor-Cron-Minuten
		linst_cl* linstp=0;
		vector<string> benutzer; // Benutzer aus /etc/passwd, bearbeitet durch setzbenutzer(&user)
		uchar obsotiff=0; // 1 = tiff wird von der source verwendet
	protected:
    virtual void lgnzuw(); // in vorgaben, lieskonfein, getcommandl0, getcommandline, rueckfragen
		void setztmpcron();
		void tucronschreib(const string& zsauf,const uchar cronzuplanen,const string& cbef);
		void vischluss(string& erg);
	public:
		hcl(const int argc, const char *const *const argv);
		~hcl();
		int Log(const string& text,const bool oberr=0,const short klobverb=0) const;
    int pruefinstv();
    void lieskonfein(const string& DPROG);
		void setzlog();
		int zeighilfe(const stringstream *const erkl);
		void pruefsamba(const vector<const string*>& vzn,const svec& abschni,const svec& suchs,const char* DPROG,const string& cuser);
#ifdef immerwart
		void lieszaehlerein(ulong *arp=0,ulong *tap=0,ulong *map=0,struct tm *lap=0, string *obempfp=0,string *obgesap=0,const uchar obstumm=0);
		void schreibzaehler(const string* obempfp=0, const string* obgesap=0);
#else // immerwart
		void lieszaehlerein(ulong *arp=0,ulong *tap=0,ulong *map=0,struct tm *lap=0, const uchar obstumm=0);
		void schreibzaehler();
#endif // immerwart
		void setzzaehler();
		int holvomnetz(const string& datei,const string& vors=defvors,const string& nachs=defnachs);
		int kompilbase(const string& was,const string& endg);
		int kompiliere(const string& was,const string& endg,const string& vorcfg=nix,const string& cfgbismake=s_dampand);
		int kompilfort(const string& was,const string& vorcfg=nix,const string& cfgbismake=s_dampand,uchar ohneconf=0);
		double progvers(const string& prog);
		void prueftif(string aktvers);
		void zeigversion(const string& ltiffv=nix);
		void zeigkonf();
		void gcl0();
		uchar pruefcron(const string& cm);
		void dodovi(const svec d1,const svec d2);
		void dovi();
		virtual void schlussanzeige();
		void update(const string& DPROG);
		void reduzierlibtiff();
		void setzbenutzer(string *user);
}; // class hcl
