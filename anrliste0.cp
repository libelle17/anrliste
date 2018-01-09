#include "kons.h"
#include "DB.h"
#define VOMHAUPTCODE
#include "anrliste0.h"

enum T_
{
 T_zu_schreiben,
 T_VorgbAllg,
 T_VorgbSpeziell,
 T_MusterVorgb,
 T_rueckfragen,
 T_autokonfschreib,
 T_cm_k,
 T_cronminuten_l,
 T_Alle_wieviel_Minuten_soll,
 T_autoupd_k,
 T_autoupd_l,
 T_Programm_automatisch_aktualisieren,
 T_Sollen_neue_Programmversionen_von,
 T_automatisch_installiert_werden,
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
 // T_cm_k
 {"cm","cm"},
 // T_cronminuten_l
 {"cronminuten","cronminutes"},
 // T_Alle_wieviel_Minuten_soll
 {"alle wieviel Minuten soll ","every how many minutes shall "},
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
 {"",""}
}; // char const *DPROG_T[T_MAX+1][SprachZahl]=

class TxB Tx((const char* const* const* const*)DPROG_T);

uchar ZDB=0; // fuer Zusatz-Debugging (SQL): ZDB 1, sonst: 0
const char *logdt="/var/log/" DPROG "vorgabe.log";//darauf wird in kons.h verwiesen; muss dann auf lgp zeigen;

using namespace std;

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
 const char* const sarr[]={"language","cronminut","autoupd","logvz","logdname","oblog"};
 agcnfA.initd(sarr,sizeof sarr/sizeof *sarr);
 gcl0();
} // getcommandl0

void hhcl::VorgbAllg()
{
 Log(violetts+Tx[T_VorgbAllg]+schwarz);
 cronminut=2;
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
	erkl<<blau<<schwarz;
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
 } // if (rzf)
} // void hhcl::rueckfragen()

// wird aufgerufen in: main
void hhcl::autokonfschreib()
{
 Log(violetts+Tx[T_autokonfschreib]+schwarz+", "+Tx[T_zu_schreiben]+((rzf||obkschreib)?Txk[T_ja]:Txk[T_nein]));
 if (rzf||obkschreib) {
 } // if (rzf||obkschreib)
} // void hhcl::autokonfschreib

// wird aufgerufen in: main
void hhcl::zeigueberschrift()
{
 char buf[20]; snprintf(buf,sizeof buf,"%.5f",versnr);
 ::Log(schwarzs+Txk[T_Programm]+blau+mpfad+schwarz+", V: "+blau+buf+schwarz,1,1);
} // void hhcl::zeigueberschrift


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
  exit(8);
 if (hhi.obvi) hhi.dovi();
 if (hhi.zeigvers) {
   hhi.zeigversion();
 } // if (hhi.zeigvers)
 hhi.autokonfschreib();
 hhi.schlussanzeige();
 return 0;
} // int main
