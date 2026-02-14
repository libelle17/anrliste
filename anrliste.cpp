// '//α' oder '//ω' als Kommentar sind nur fuer die Verwendung dieses Programms als Programmvorlage wichtig
const double& versnr= //α
#include "versdt"
;
#include "kons.h"
#include "DB.h" 
#include <tiffio.h>
#define VOMHAUPTCODE // um Funktionsdefinition manchmal mit "__attribute__((weak)) " versehen zu können //ω
#include "anrliste.h"
#include "tr64.h"
// fuer verschiedene Sprachen //α
char const *DPROG_T[T_MAX+1][SprachZahl]={
	// T_virtVorgbAllg
	{"virtVorgbAllg()","virtgeneralprefs()"},
	// T_pvirtVorgbSpeziell
	{"pvirtVorgbSpeziell()","pvirtspecialprefs()"},
	// T_virtMusterVorgb
	{"virtMusterVorgb()","virtsampleprefs"},
	// T_pvirtvorrueckfragen
	{"pvirtvorrueckfragen()","pvirtbeforecallbacks()"},
	// T_virtrueckfragen
	{"virtrueckfragen()","virtcallbacks()"},
	// T_virtpruefweiteres
	{"virtpruefweiteres()","virtcheckmore()"},
	// T_virtmacherkl_Tx_lgn
	{"pvirtmacherkl, Tx.lgn: ","pvirtmakeexpl, Tx.lgn: "},
	//	T_Fehler_beim_Pruefen_von
	{"Fehler beim Pruefen von: ","Error while examining: "},
	// T_st_k
	{"st","st"},
	// T_stop_l
	{"stop","stop"},
	// T_DPROG_anhalten
	{DPROG " anhalten","stop " DPROG},
	// T_anhalten
	{"anhalten()","stop()"},
	// T_Cron_Aufruf_von
	{"Cron-Aufruf von '","cron call of '"},
	// T_gestoppt
	{"' gestoppt.","' stopped."},
	// T_n_k
	{"n","n"},
	// T_dszahl_l
	{"dszahl","reccount"},
	// T_Zahl_der_aufzulistenden_Datensaetze_ist_zahl_statt
	{"Zahl der aufzulistenden Datensaetze = <zahl> statt","No. of listed entries = <no> instead of"},
	// T_Datenbank_nicht_initialisierbar_breche_ab
	{"Datenbank nicht initialisierbar, breche ab","database init failed, stopping"},
	// T_Fuege_ein
	{"Fuege ein: ","Inserting: "}, //ω
	// T_eindeutige_Identifikation
	{"eindeutige Identifiaktion","unique ID"},
	// T_ID_aus_Fritzbox
	{"ID aus der Fritzbox","ID from the fritzbox"},
	// T_Benutzer_fuer_Fritzbox,
	{"Benutzer fuer Fritzbox","password for fritzbox"},
	// T_Passwort_fuer_Fritzbox,
	{"Passwort fuer Fritzbox (Achtung: nur schwach verschluesselt!)","password for fritzbox (caution: only weakly encrypted!)"},
	// T_pruefanrufe
	{"pruefanrufe()","checkcalls()"},
	// T_Anruftyp_1_ankommend_3_abgehend
	{"Anruftyp: 1=ankommend, 2=ankommend im Abwesenheit, 3=abgehend","type of call: 1=incoming, 2=incoming absent, 3=outgoing"},
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
	{"Nummerntyp","number type"},
	// T_Port
	{"Port","port"},
	// T_Verbindungsdauer
	{"Verbindungsdauer","Connection duration"},
	// T_Zahl
	{"Zahl","count"},
	// T_Telefonprotokoll_der_Fritzbox
	{"Telefonprotokoll der Fritzbox","Connection journal of the fritzbox"},
	// T_Datensaetze_gelesen
	{" Datensaetze gelesen"," data sets read"},
	// T_Datensaetze_eingetragen
	{" Datensaetze eingetragen"," data sets inserted"},
	// T_tabname_l,
	{"tabname","tabname"},
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
	// T_listt_k
	{"listt","listt"},
	// T_listtel_l
	{"listtel","listtel"},
	// T_tu_listt
	{"tu_listt()","do_listt()"},
	// T_listet_Datensaetze_aus
	{"listet Datensaetze aus `","lists entries from `"},
	// T_mit_Erfolgskennzeichen_auf
	{"` mit Erfolgskennzeichen auf","` with success flag"},
	// T_s_k
	{"s","s"},
	// T_suche_l
	{"suche","search"},
	// T_suche_in_verarbeiteten_Faxen_nach
	{"Suche in verarbeiteten Faxen nach <string>: ","Look in processed faxes for <string>: "},
	//  T_holanr,
	{"holanr()","fetchcall()"},
	{"",""} //α
}; // char const *DPROG_T[T_MAX+1][SprachZahl]=

class TxB Tx((const char* const* const* const*)DPROG_T);
const char sep = 9; // geht auch: "[[:blank:]]"
const char *logdt="/var/log/" DPROG "vorgabe.log";//darauf wird in kons.h verwiesen;
pidvec pidw;
const unsigned ktage=1; // kurzes Intervall fuer Faxtabellenkorrektur, 1 Tag
const unsigned mtage=30; // mittleres Intervall fuer Faxtabellenkorrektur, 1 Monat
const unsigned ltage=73000; // langes Intervall fuer Faxtabellenkorrektur, 200 Jahre

using namespace std; //ω

void anrufcl::clear()
{
	id.clear();
	type.clear();
	caller.clear();
	called.clear();
	callednumber.clear();
	name.clear();
	numbertype.clear();
	device.clear();
	port.clear();
	date.clear();
	duration.clear();
	count.clear();
} // void anrufcl::clear

hhcl::hhcl(const int argc, const char *const *const argv):dhcl(argc,argv,DPROG,/*mitcron*/1) //α
{
 // mitcron=0; //ω
} // hhcl::hhcl //α
// Hier neue Funktionen speichern: //ω
//α
// wird aufgerufen in lauf
void hhcl::virtVorgbAllg()
{
	hLog(violetts+Tx[T_virtVorgbAllg]+schwarz); //ω
	dhcl::virtVorgbAllg(); //α
} // void hhcl::virtVorgbAllg

// wird aufgerufen in lauf
void hhcl::pvirtVorgbSpeziell()
{
	hLog(violetts+Tx[T_pvirtVorgbSpeziell]+schwarz);
	virtMusterVorgb(); //ω
	dhcl::pvirtVorgbSpeziell(); //α
} // void hhcl::pvirtVorgbSpeziell

// wird aufgerufen in lauf
void hhcl::virtinitopt()
{ //ω
	// Kopiervorlage:
	// opn<<new optcl(/*pname*/"pname",/*pptr*/pptr,/*art*/pstri,/*kurzi*/T_kurz_k,/*langi*/T_lang_l,/*TxBp*/&Tx,/*Txi*/T_Option_erklaert,/*wi*/1,/*Txi2*/T_Option_Nachtext,/*rottxt*/nix,/*wert*/1,/*woher*/!pname.empty(),/*Txtrf*/{},/*obno*/1,/*refstr*/0,/*obfragz*/0,/*fnobfragz*/0,/*fnnachhz*/&hcl::fu1,/*fnvorhz*/0,/*sonderrf*/0);
	opn<<new optcl(/*pname*/"tabname",/*pptr*/&tabname,/*part*/pstri,T_tb_k,T_tabname_l,/*TxBp*/&Txd,/*Txi*/T_verwendet_die_Tabelle_string_anstatt,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!tabname.empty(),Txd[T_Tabellenname_in]+dblaus+dbq+schwarz+"':");
	opn<<new optcl(/*pname*/"fbusr",/*pptr*/&fbusr,/*part*/pstri,T_fbusr_k,T_fbusr_l,/*TxBp*/&Tx,/*Txi*/T_verwendet_fuer_die_Fritzbox_den_Benutzer_string_anstatt,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!fbusr.empty(),Tx[T_Benutzer_fuer_Fritzbox]);
	opn<<new optcl(/*pname*/"fbpwd",/*pptr*/&fbpwd,/*part*/ppwd,T_fbpwd_k,T_fbpwd_l,/*TxBp*/&Tx,/*Txi*/T_verwendet_fuer_die_Fritzbox_das_Passwort_string,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!fbpwd.empty(),Tx[T_Passwort_fuer_Fritzbox],/*obno*/0,/*refstr*/&fbusr);
	opn<<new optcl(/*pptr*/&listt,/*art*/puchar,T_listt_k,T_listtel_l,/*TxBp*/&Tx,/*Txi*/T_listet_Datensaetze_aus,/*wi*/1,/*Txi2*/T_mit_Erfolgskennzeichen_auf,/*rottxt*/tabname,/*wert*/1,/*woher*/1);
	opn<<new optcl(/*pptr*/&suchstr,/*art*/pstri,T_s_k,T_suche_l,/*TxBp*/&Tx,/*Txi*/T_suche_in_verarbeiteten_Faxen_nach,/*wi*/1,/*Txi2*/T_MAX,/*rottxt*/nix,/*wert*/-1,/*woher*/1);
	opn<<new optcl(/*pptr*/&dszahl,/*art*/pdez,T_n_k,T_dszahl_l,/*TxBp*/&Tx,/*Txi*/T_Zahl_der_aufzulistenden_Datensaetze_ist_zahl_statt,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/1); //α //ω
	dhcl::virtinitopt(); //α
} // void hhcl::virtinitopt

// wird aufgerufen in lauf
void hhcl::pvirtmacherkl()
{
	hLog(violetts+Tx[T_virtmacherkl_Tx_lgn]+schwarz+ltoan(Tx.lgn));
//	erkl<<violett<<DPROG<<blau<<Txk[T_tut_dieses_und_jenes]<<schwarz; //ω 
} // void hhcl::pvirtmacherkl //α
//ω
//α
// wird aufgerufen in lauf
void hhcl::virtMusterVorgb()
{
	hLog(violetts+Tx[T_virtMusterVorgb]+schwarz); //ω
	dbq="faxeinp";
	dhcl::virtMusterVorgb(); //α
} // void hhcl::MusterVorgb

// wird aufgerufen in lauf
void hhcl::pvirtvorzaehler()
{ //ω
} // void hhcl::virtvorzaehler() //α
//ω
// wird aufgerufen in lauf //α
void hhcl::virtzeigversion(const string& ltiffv/*=nix*/)
{
	dhcl::virtzeigversion(ltiffv);  //ω
} // void hhcl::virtzeigversion //α
//ω
//α
// wird aufgerufen in lauf
void hhcl::pvirtvorrueckfragen()
{
	hLog(violetts+Tx[T_pvirtvorrueckfragen]+schwarz); //ω
} // void hhcl::pvirtvorrueckfragen //α

//α
// wird aufgerufen in lauf
void hhcl::virtpruefweiteres()
{
	fLog(violetts+Tx[T_virtpruefweiteres]+schwarz,obverb,oblog); //ω
	if (initDB()) 
		exit(schluss(10,Tx[T_Datenbank_nicht_initialisierbar_breche_ab])); //α //ω
	pruefanrufe(My,tabname,obverb,oblog);
	hcl::virtpruefweiteres(); // z.Zt. leer //α
} // void hhcl::virtpruefweiteres

// wird aufgerufen in lauf
void hhcl::virtzeigueberschrift()
{ //ω
	// hier ggf. noch etwas an 'uebers' anhaengen //α
	hcl::virtzeigueberschrift();
} // void hhcl::virtzeigueberschrift
//ω
//α
// Parameter -st / --stop
// wird aufgerufen in: main
void hhcl::anhalten()
{
	hLog(violetts+Tx[T_anhalten]+schwarz);
	// crontab
	/*
	setztmpcron();
	for(int iru=0;iru<1;iru++) {
		const string befehl=
			"bash -c 'grep \""+saufr[iru]+"\" -q <(crontab -l)&&{ crontab -l|sed \"/"+zsaufr[iru]+"/d\">"+tmpcron+";crontab "+tmpcron+";};:'";
		systemrueck(befehl,obverb,oblog,*//*rueck=*//*0,*//*obsudc=*//*1);
	} // 	for(int iru=0;iru<2;iru++)
  */
	pruefcron("0"); // soll vor Log(Tx[T_Verwende ... stehen
	fLog(blaus+Tx[T_Cron_Aufruf_von]+schwarz+mpfad+blau+Tx[T_gestoppt]+schwarz,1,oblog); //ω
} // void hhcl::anhalten() //α
//ω
//α
void hhcl::pvirtnachrueckfragen()
{
	// if (initDB()) exit(schluss(10,Tx[T_Datenbank_nicht_initialisierbar_breche_ab]));  //ω
		if (initDB()) {
			exit(schluss(10,Tx[T_Datenbank_nicht_initialisierbar_breche_ab]));
		}
		if (listt ||!suchstr.empty()) {
			tu_listt("1",suchstr);
		}
} // void hhcl::pvirtnachrueckfragen //α
//ω
void hhcl::pvirtfuehraus() //α
{ //ω
	if (!listt && suchstr.empty()) {
		holanr();
	}
} // void hhcl::pvirtfuehraus  //α

// wird aufgerufen in lauf
void hhcl::virtschlussanzeige()
{   //ω
	dhcl::virtschlussanzeige(); //α
} // void hhcl::virtschlussanzeige
 
// wird aufgerufen in: main
void hhcl::virtautokonfschreib()
{
// const int altobverb=obverb;
// obverb=1;
	hLog(violetts+Txk[T_autokonfschreib]+schwarz+", "+Txk[T_zu_schreiben]+((rzf||hccd.obzuschreib)?Txk[T_ja]:Txk[T_nein])); //ω
	struct stat kstat{0}; //α
	if (lstat(akonfdt.c_str(),&kstat))
		hccd.obzuschreib=1;
	if (rzf||hccd.obzuschreib) {
		hLog(gruens+Txk[T_schreibe_Konfiguration]+schwarz);
		// restliche Erklaerungen festlegen
		////    agcnfA.setzbem("language",sprachstr);
		hcl::virtautokonfschreib(); //ω
	} // if (rzf||hccd.obzuschreib) //α
// obverb=altobverb;
} // void hhcl::virtautokonfschreib

hhcl::~hhcl() 
{ //ω
} // hhcl::~hhcl //α

// wird nur im Fall obhilfe==3 nicht aufgerufen
void hhcl::virtlieskonfein()
{
	const int altobverb{obverb};
	//	obverb=1;
	hLog(violetts+Txk[T_virtlieskonfein]+schwarz);
	hcl::virtlieskonfein(); //ω
	hLog(violetts+Txk[T_Ende]+Txk[T_virtlieskonfein]+schwarz); //α
	obverb=altobverb;
} // void hhcl::virtlieskonfein() //ω

// Kernprogramm, holt die Anrufe und traegt sie ein
int hhcl::holanr() // fetchcall()
{
	hLog(violetts+Tx[T_holanr]+schwarz);
	const size_t aktc{0};
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
/*
	if (obverb>1) {
		caus<<"fbuser: '"<<fbusr<<"'"<<endl;
		caus<<"fbpwd: '"<<fbpwd<<"'"<<endl;
	}
*/
    string filename("fbpwd.txt");
    fstream file_out;

    file_out.open(filename, std::ios_base::out);
    if (!file_out.is_open()) {
        cout << "failed to open " << filename << '\n';
    } else {
        file_out <<fbpwd<< endl;
    }

	tr64cl tr64(fbusr,fbpwd);
  std::string buffer,nurl;
  tr64.fragurl("x_contact","X_AVM-DE_OnTel:1","GetCallList",&buffer,0,0,obverb);

	if (obverb) {
		std::cout<<"Buffer: "<<endl<<buffer<<std::endl;
	}
	// bei falschem Passwort hier noch Fehler 401 abfangen
  holraus(buffer,"NewCallListURL",&nurl,0,obverb);
  holurl(nurl,&buffer,obverb);
	// caus<<buffer<<endl;
  size_t pos=0,enr=0;
	RS rins(My,tabname); 
	while ((pos=holraus(buffer,"Call",&nurl,pos,obverb))) {
		stringstream ausg;
		ausg<<++enr<<": ";
		size_t ipos=0;
		tm vt({0});
		stringstream vts;
		anrufcl ar;
		for(size_t tzn=0;tzn<tz.size();tzn++) {
			std::string it;
			size_t tza=(ar.type=="3"?(tzn==2?3:(tzn==3?2:tzn)):tzn);
			ipos=holraus(nurl,tz[tza],&it,ipos,obverb);
			switch (tza) {
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
		RS such(My,"SELECT datum FROM `"+tabname+"` WHERE typ="+ar.type+" AND Datum='"+vts.str()+"' AND Name ='"+ar.name+"'"\
				" AND Rufnummer=if(typ='3','"+ar.called+"','"+ar.caller+"')"\
				" AND EigeneNr=if(typ='3','"+ar.caller+"','"+ar.called+"') AND Dauer='"+ar.duration+"'",aktc,ZDB);//Nst wg. Zeichensatz weggel.
		if (!such.obqueryfehler) {
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
				rins.tbins(&einf,aktc,/*sammeln=*/1,/*oberb=*/ZDB,/*idp=*/0,/*eindeutig=*/0);  // einfuegen
				if (!rins.fnr)
					egz++;
				fLog(blaus+ausg.str()+schwarz,1,oblog);
			} else {
				fLog(ausg.str(),obverb,oblog);
			} // 					if (!cerg || !*cerg)
		} // 				if (!such.obqueryfehler)
	} // 	while ((pos=holraus
	rins.tbins(0,aktc,/*sammeln=*/0,/*oberb=*/ZDB,/*idp=*/0,/*eindeutig=*/0);  // einfuegen
	fLog(blaus+ltoan(dsz)+schwarz+Tx[T_Datensaetze_gelesen],1,0);
	fLog(blaus+ltoan(egz)+schwarz+Tx[T_Datensaetze_eingetragen],1,0);
	// std::cout<<buffer<<std::endl;
	return EXIT_SUCCESS;
}

// wird aufgerufen in: main
void hhcl::pruefanrufe(DB *My, const string& tabelle, const int obverb, const int oblog, const uchar direkt/*=0*/)
{
	fLog(violetts+Tx[T_pruefanrufe]+schwarz,obverb,oblog);
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
		Tabelle taba(My,tabelle,felder,sizeof felder/sizeof* felder,indices,sizeof indices/sizeof *indices,0,0,
				Tx[T_Telefonprotokoll_der_Fritzbox]/*//,"InnoDB","utf8","utf8_general_ci","DYNAMIC"*/);
		if (taba.prueftab(aktc,obverb)) {
			fLog(rots+Tx[T_Fehler_beim_Pruefen_von]+schwarz+tabelle,1,1);
			exit(11);
		}
	} // if (!direkt)
} // int hhcl::pruefanrufe(DB *My, string touta, int obverb, int oblog, uchar direkt=0)

// wird aufgerufen in: main (2x)
void hhcl::tu_listt(const string& oberfolg, const string& suchstr)
{
	// "... submid id ()" wuerde zu Mysql-Fehler fuehren
	hLog(violetts+Tx[T_tu_listt]+schwarz);
	const size_t aktc=0;
	char ***cerg;
/*	RS listt(My,"SELECT Ueberm p0, Submid p1, Faxname p2, Empfaenger p3, Fax p4, Erfolg p5 FROM ("
			"SELECT * FROM ("
			"SELECT DATE_FORMAT(transe,'%d.%m.%y %H:%i:%s') Ueberm, Submid, RIGHT(CONCAT(space(75),LEFT(Docname,75)),75) Faxname, "
			"RIGHT(CONCAT(SPACE(30),LEFT(rcname,30)),30) Empfaenger, rcfax Fax, Erfolg, transe "
			"FROM `"+touta+"` WHERE "+(submids.length()<=2?"Erfolg = "+oberfolg+" ":"submid in "+submids+" ")+
			" ORDER BY transe DESC"+(submids.length()<=2?" LIMIT "+dszahl:"")+") i "
			" ORDER BY transe LIMIT 18446744073709551615) i",aktc,ZDB); */
	RS lista(My,"SELECT * FROM ("
		"SELECT Datum,case Typ when 1 then '->' when 2 then '->|' when 3 then '<-' when 9 then '->>' when 11 then 'fx<-' else Typ end,Name,Rufnummer,Nebenstelle,EigeneNr,angerNr,Dauer,Nummerntyp,Port,Id,eind from faxeinp.anrufe "
		+(suchstr.empty()?"":" WHERE Rufnummer LIKE '%"+suchstr+"%' ")+
		"ORDER BY eind DESC LIMIT "+dszahl+
		") i ORDER BY datum;",aktc,ZDB);
	/*if (submids.length()<=2)
		cout<<violett<<Tx[T_Letzte]<<blau<<dszahl<<violett<<(oberfolg=="1"?Tx[T_erfolgreich]:Tx[T_erfolglos])<<Tx[T_versandte_Faxe]<<schwarz<<endl; */
	while (cerg=lista.HolZeile(),cerg?*cerg:0) {
		cout<<blau<<setw(17)<<cjj(cerg,0)<<"|"<<violett<<setw(4)<<cjj(cerg,1)<<schwarz<<"|"<<blau<<setw(30)<<cjj(cerg,2)
			<<"|"<<schwarz<<setw(15)<<cjj(cerg,3)<<"|"<<blau<<setw(10)<<cjj(cerg,4)
			<<"|"<<schwarz<<setw(11)<<cjj(cerg,5)<<"|"<<blau<<setw(6)<<cjj(cerg,6)
			<<"|"<<schwarz<<setw(5)<<cjj(cerg,7)<<"|"<<blau<<setw(3)<<cjj(cerg,8)
			<<"|"<<schwarz<<setw(2)<<cjj(cerg,9)<<"|"<<blau<<setw(5)<<cjj(cerg,10)
			<<"|"<<schwarz<<setw(5)<<cjj(cerg,11)
			<<"|"<<schwarz<<endl;
	} // while (cerg=lista.HolZeile(),cerg?*cerg:0) 
} // tu_listt

int main(int argc,char** argv) //α
{
	if (argc>1) { //ω
	} //α
	hhcl hhi(argc,argv); // hiesige Hauptinstanz, mit lngzuw, setzlog und pruefplatte
	hhi.lauf(); // Einleitungsteil mit virtuellen Funktionen, 
	// mit virtVorgbAllg,pvirtVorgbSpeziell,initopt,parsecl,pvirtmacherkl,zeighilfe,virtlieskonfein,verarbeitkonf,lieszaehlerein,MusterVorgb,dovi,dovs,virtzeigversion
	// virtautokonfschreib,update,
	return hhi.retu;
} // int main 

void hhcl::virttesterg()
{
} //ω
