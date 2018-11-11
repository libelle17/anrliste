# kompiliert alle *.cpp-Dateien im aktuellen Verzeichnis
# statt erstmaliger Verwendung bitte "./install.sh" aufrufen, dort wird das hier eingeschlossene "vars" erstellt und  ggf. 'make' installiert
# nach "touch entwickeln" wird eine Datei 'versdt' erstellt, deren Inhalt, eine Versionsnummer, bei jedem Kompiliervorgang um 0.0001 erhoeht wird
# und die in die man_de und man_en-Datei eingebaut wird sowie ueber
#  const double& versnr=
#  #include versdt
#  ;
# auch in den c(++)-Quellcode eingebaut werden kann

# Aufrufvarianten:
# "mitpg=1 make <..>" => es wird mit/fuer postgres kompiliert und gelinkt, die Praeprozessordirektive "mitpostgres" wird dem Compiler uebergeben
# "make glei" => der Compiler wird vorher nicht ueberprueft
# "make opt" => optimiere mit -O; kompiliere alles neu
# "make opt2" => optimiere mit -O2; kompiliere alles neu
# "make opt3" => optimiere mit -O3; kompiliere alles neu
# "make opts" => optimiere mit -Os, nach Groesse; kompiliere alles neu
# "make optfast" => optimiere mit -Ofast, nach Ausfuerungsgeschwindigkeit; kompiliere alles neu
# "make optg" => optimiere mit -Og, zum Debuggen; kompiliere alles neu
# "make debug" => erstelle mit -g;
# "make debugnew" oder "make debugneu" => erstelle alles neu mit -g;
# "make new" oder "make neu" => kompiliere alles neu
# "make distclean" => loesche Objekt- und ausfuehrbare Dateien im Kompilierverzeichnis
# "make fernclean" => loesche installierte Objekt- und ausfuehrbare Dateien
# "make clean" => loesche Objekt- und ausfuehrbare Dateien einschliesslich installierter Version
# "make confclean" => loescht die Konfigurationsdatei $(INSTEXEC).conf nach Rueckfrage, falls vorhanden
# "make altc" => kompiliere mit -std=gnu++11
# "make anzeig" => zeige Informationen zu Programm, Quelldateien und Compiler an
# "make install" => installiere die erstellte Datei in den kuerzesten Pfad aus $PATH, der '/usr/' enthaelt,
#                   installiert man-Seiten aus man_de und man_en, ferner *.html-Dateien und eine README.md-Datei fuer den git-Server
# "make stumm und make stumminst" => zum Aufruf aus vim
# "make git" => aktualisiert die Datei auf dem zugeordneten git-Server
# "make giterlaub" => speichert die Daten zum Hochladen auf den git-Server
# "make version" => kompilieren mit opts, installieren und aktualisieren auf git-Server mit einheitlicher Dateiversion
# "make transfer <zielvz>" => kopieren der Programmdateien abzüglich bestimmter Kommentare in Zielverzeichnis <zielvz>
# "make verschieb" => wie transfer, mit ../<DPROG>rein als Zielverzeichnis
# "make vsneu" => wie verschieb, löscht vorher das als Zielverzeichnis (geht nur, wenn das github-Repository vorher gelöscht ist)
# "make ruf" => ruft das Programm auf
# "make rufv" => ruft das Programm mit -v auf
# "make uninstall" => deinstalliert alles, frägt noch manchmal rück
# "make allesweg" => deinstalliert alles, beantwortet Rückfragen mit 'y'
# "make neuproj" => kopiert Dateien für neues Projekt in Verzeichnis fuer neues Projekt

ICH::=$(firstword $(MAKEFILE_LIST))
SRCS::=$(wildcard *.cpp)
OBJ::=$(SRCS:.cpp=.o)
# wenn aus vi aufgerufen, kein unnoetigen Ausgaben, BA=bedingte Ausgabe, BFA=bedingte Fehlerausgabe
BA::=&1
BFA::=2>>fehler.txt
ifdef ausvi
 BA::=/dev/null
endif
#PROGRAM::=$(shell basename $(CURDIR))
#EXPFAD=/usr/local/sbin
EXPFAD::=$(shell echo $(PATH) | tr -s ':' '\n' | grep /usr/ | head -n 1)
EXPFAD::=$(shell echo $(PATH) | tr -s ':' '\n' | grep /usr/ | awk '{ print length, $$0 }' | sort -n -s | cut -d" " -f2- | head -n1)

#// ifneq ($(shell g++-6 --version >$(KR); echo $$?),0)
#//  CCName::=g++
#//  CFLAGS::=$(CFLAGS) -std=gnu++11 # 7.8.17 nicht nötig für opensuse42, hinderlich für fedora; 5.9.17: geht nicht mehr (wg. auto)
#// else
# minimal erforderliche g++-Hauptversion
MINGCCNR::=6
#// endif
#// 0=Version fehlt, 1=Version ist da
#// GCCAB6::=$(shell expr `g++-6 -dumpversion 2>/dev/null||g++-7 -dumpversion 2>/dev/null||echo 0` \>= 6) 
#// ifeq ('$(GCCAB6)','0')
#// CCName=g++-6
#// endif
# maximal verfügbare g++-Version, falls die Verknüpfungen in /usr/bin stehen und evtl. /usr/bin/g++ nicht auf die höchste verknüpft ist
MAXGCC::=$(shell { ls /usr/bin/g++* 2>/dev/null||echo 0;}|tail -n1)
# deren Hauptversionsnummer
MAXGCCNR::=$(shell echo $(MAXGCC)|cut -d- -f2)
#1=verfügbare Version höher als die minimal notwendige, 0=nicht
GCCNEU::=$(shell expr $(MAXGCCNR) \> $(MINGCCNR))
# 1=minimal notwendige Version verfügbar, 0=nicht
GCCOK::=$(shell expr $(MAXGCCNR) \>= $(MINGCCNR))
# 1=Debian usw., 2=Opensuse, 3=Fedora usw., 4=Magieia, 5=Manjaro usw.
DISTR::=$(shell which apt>/dev/null 2>&1&&echo 1||{ which zypper>/dev/null 2>&1&&echo 2||{ which dnf>/dev/null 2>&1||which yum>/dev/null 2>&1&&echo 3||{ which urpmi.update>/dev/null 2>&1&&echo 4||{ which pacman>/dev/null 2>&1&&echo 5||echo 0;};};};})
ifeq ($(GCCNEU),1)
	MINGCCNR::=$(MAXGCCNR)
endif
CCName::=g++-$(MINGCCNR)
ifeq ($(DISTR),1)
	CCName::=g++-$(MINGCCNR)
	CCInst::=gcc-$(MINGCCNR) g++-$(MINGCCNR)
endif
ifeq ($(DISTR),2)
	OBEINS::=1
endif
ifeq ($(DISTR),3)
	CCName::=g++
	OBEINS::=1
endif
ifeq ($(OBEINS),1)
	CCInst::=gcc$(MINGCCNR) gcc$(MINGCCNR)-c++
endif
-include vars # wird durch install.sh generiert; CCInst muss vorher definiert werden, DPROG und GDAT dürfen nur nachher verwendet werden
CFLAGS::=-c -Wall
LDFLAGS::=
ifneq ($(libmac),)
	CFLAGS::=$(CFLAGS) `mysql_config --cflags`
	LDFLAGS::=`mysql_config --libs`
endif
ifneq ($(LT),)
	LDFLAGS::=$(LDFLAGS) -ltiff
endif
ifneq ($(LBOOST),)
	LDFLAGS::=$(LDFLAGS) -lboost_iostreams -lboost_locale
endif
ifneq ($(LACL),)
	LDFLAGS::=$(LDFLAGS) -lacl
endif
ifneq ($(LCURL),)
	LDFLAGS::=$(LDFLAGS) -lcurl
endif
ifdef mitpg
	CFLAGS::=$(CFLAGS) -I/usr/include/pgsql -Dmitpostgres
	LDFLAGS::=$(LDFLAGS) -lpq
endif
PROGGROSS::=`echo $(DPROG) | tr a-z A-Z`
EXEC::=$(DPROG)
INSTEXEC::=$(EXPFAD)/$(EXEC)
GDAT::=$(DTN:inst.log=)
GDAT::=$(GDAT:uninstallinv=)
GDAT::=$(GDAT:Makefile=Makefile.roh)
ifeq ($(DISTR),1)
	COMP::=$(COMP) $(CCInst)
endif
CC::=$(CCName) # CC=$(SUDC)$(CCName)
libmcd::=$(libmc)-$(dev)
libmc1d::=$(libmac)-$(dev)
pgd::=postgresql-$(dev)
SUDC::=
ifneq ($(shell echo $$EUID),0)
	SUDC::=sudo 
endif
slc::=$(SUDC)/sbin/ldconfig
# deinstallieren und Ueberschrift vormerken
# uninst=printf '$(UPR)$(1)\nprintf "$$blau%%s$$reset\\n" "$(UPR)$(1)"\n'>>$(UNF);
# uninstd=printf '$(UDPR)$(1)\nprintf "$$blau%%s$$reset\\n" "$(UDPR)$(1)"\n'>>$(UNF); # direkt
# in Protokoll suchen und ...
# sunins=test -f $(UNF)&&grep -q '$(1)' $(UNF)||{ $(call uninst,$(2))};
# suninsd=test -f $(UNF)&&grep -q '$(1)' $(UNF)||{ $(call uninstd,$(2))}; # direkt
# installieren und ...
# Selbes Wort in Protokoll suchen wie deinstallieren
# iunins=$(IPR)$(1) &&{ $(call sunins,$(1),$(2))};
# iuninsd=$(IPR)$(1) &&{ $(call suninsd,$(1),$(2))}; # direkt
# i1unin=$(call iunins,$(1),$(1))
# i1unind=$(call iuninsd,$(1),$(1)) # direkt
# i_unins=$(IP_R)$(1) &&{ $(call sunins,$(1),$(2))};
# i_uninsd=$(IP_R)$(1) &&{ $(call suninsd,$(1),$(2))}; # direkt
# Programm suchen, ggf. installieren und ...
# siunins= $(SPR)$(1)>$(KR)||{ $(call iunins,$(1),$(2))};
# siuninsd= $(SPR)$(1)>$(KR)||{ $(call iuninsd,$(1),$(2))}; # direkt
# i1siun=$(call siunins,$(1),$(1))
# i1siund=$(call siuninsd,$(1),$(1)) # direkt
# si_unins=$(SPR)$(1)>$(KR)||{ $(call i_unins,$(1),$(2))};
# GROFFCHECK::=$(call i1siund,$(PGROFF)):

DEPDIR ::= .d
$(shell mkdir -p $(DEPDIR)>$(KR))
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

# POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d 2>/dev/null

rot::="\033[1;31m"
gruen::="\033[0;32m"
#blau="\033[0;34;1;47m"
blau::="\033[1;34m"
reset::="\033[0m"

MANV::=/usr/share/man
ifeq ('$(wildcard man_en)','')
INSTenMAN::=
else
INSTenMAN::=$(MANV)/man1/$(DPROG).1.gz
endif
_MAN::=$(subst man_en,,$(wildcard man_??))
FLANGS::=$(patsubst man_%,%,$(_MAN))
INST_MAN::=$(patsubst man_%,$(MANV)/%/man1/$(DPROG).1.gz,$(_MAN))
$(foreach lang,$(FLANGS), $(eval INST$(lang)MAN=$(filter $(MANV)/$(lang)/%,$(INST_MAN))))
MANS::=$(wildcard man_en)
MANS+=$(_MAN)
HTMLS::=$(patsubst %,%.html,$(MANS))
GZS::=$(patsubst %,%.gz,$(MANS))


.PHONY: all
all: anzeig weiter

.PHONY: glei
glei: anzeig $(EXEC) $(GZS) 

.PHONY: opt
opt: CFLAGS += -O
opt: neu

.PHONY: opt2
opt2: CFLAGS+= -O2
opt2: neu

.PHONY: opt3
opt3: CFLAGS+= -O3
opt3: neu

.PHONY: optfast
optfast: CFLAGS+= -Ofast
optfast: neu

.PHONY: optc
opts: CFLAGS+= -Os
opts: neu

.PHONY: optg
optg: CFLAGS+= -Og
optg: neu

.PHONY: altc
altc: CFLAGS+= -std=gnu++11
altc: CCInst::=gcc-c++
altc: CCName::=g++
altc: CC::=$(CCName) # CC=$(SUDC)$(CCName)
altc: opts

.PHONY: new
new: neu
.PHONY: neu
neu: anzeig distclean weiter

.PHONY: weiter
weiter: compiler $(EXEC) $(GZS) 


define setz_gitv
	 @D=$(1)/.git/config; GITV=$$([ -f $$D ]&&sed -n '/ *url =.*com/{s/.*com\/\([^/]*\).*/\1/p}' $$D);\
	 sed -i 's/^\(\[ -z .* \]&& GITV=\).*;/\1'$$GITV';/g' $(1)/install.sh;\
	 [ -z "$$GITV" ]&& GITV=$(EXEC);\
	 [ "$$GITV" = "$(sed 's/"//g' $(1)/gitvdt)" ]|| echo \"$$GITV\">$(1)/gitvdt;:;
endef

# davor:
# git clone ssh://git@github.com/<user>/<reponame>.git
# git clone ssh://git@github.com/libelle17/autofax.git # https://www.github.com/libelle17/autofax
# ssh-keygen -t rsa -b 4096 -f ~/.ssh/id_rsa_git -C "gerald.schade@gmx.de@github.com"
# eval "$(ssh-agent -s)"
# ssh-add ~/.ssh/id_rsa_git
# xclip -sel clip < ~/.ssh/id_rsa_git.pub
# auf http://github.com -> view profile and more -> settings -> SSH and GPG keys -> New SSH key <Titel> <key> einfuegen
git: README.md
#	@git config --global user.name "Gerald Schade"
#	@git config --global user.email "gerald.schade@gmx.de"
	@$(call machvers);
	@printf " Copying files from/ Kopiere Dateien von: %b%s%b (Version %b%s%b) -> git (%b%s%b)\n" $(blau) "$(PWD)" $(reset) $(blau) $$(cat versdt)\
  $(reset) $(blau) "$$(F1=.git/FETCH_HEAD;test -f $$F1&&{ cut -f2-< $$F1|sed 's/^\s*//';:;};[ -d .git ]&&cat .git/./config|sed -n '/url =/p')" $(reset) >$(BA) 
	-@cp -au Makefile Makefile.roh
	@[ -d .git ]||{ curl -u "$(DPROG)" https://api.github.com/user/repos -d "{\"name\":\"$(DPROG)\"}" >/dev/null; git init;git add $(GDAT:vgb.cpp=) versdt README.md;}
	$(call setz_gitv,".")
	@git config --global push.default simple
	@git add -u
	@git commit -m "Version $$(cat versdt)"
	@grep remote\ \"origin\"] .git/config >/dev/null 2>&1||git remote add origin https://github.com/$$(sed 's/"//g' gitvdt)/$(DPROG).git
	@git push -u origin master

.PHONY: giterlaub
giterlaub:
	@git config credential.helper store	
	@git config --global credential.helper 'cache --timeout=36000'

.PHONY: pull
pull:
	@git pull
	@sh configure

.PHONY: anzeig
anzeig:
# 'echo -e' geht nicht z.B. in ubuntu
	@[ "$(DPROG)" ]||{ printf "Datei/File %b'vars'%b fehlerhaft/faulty, bitte vorher/please call %b'./install.sh'%b aufrufen/before!\n" \
	       $(blau) $(reset) $(blau) $(reset);let 0;}
	@printf " %bGNU Make%b, Target file/Zieldatei: %b%s%b, before/vorher:                        \n" $(gruen) $(reset) $(rot) "$(EXEC)" $(reset) >$(BA)
	@printf " '%b%s%b'\n" $(blau) "$$(ls -l --time-style=+' %d.%m.%Y %H:%M:%S' --color=always $(EXEC) $(KF))" $(reset) >$(BA)
	@printf " Source files/Quelldateien: %b%s%b\n" $(blau) "$(SRCS)" $(reset) >$(BA)
	@printf " Compiler: %b%s%b, installed as/installiert als: %b%s%b; Compiler Parameter: %b%s%b\n"\
	        $(blau) "$(CCName)" $(reset) $(blau) "$(CCInst)" $(reset) $(blau) "$(CFLAGS)" $(reset)
	@printf " Target path for/Zielpfad fuer '%bmake install%b': %b%s%b\n" $(blau) $(reset) $(blau) "'$(EXPFAD)'" $(reset) >$(BA)
	-@rm -f fehler.txt $(KF)

.PHONY: debug debugnew debugneu
debug debugnew debugneu: DEBUG=-g 
debug: all
debugneu debugnew: neu

$(EXEC): $(OBJ)
	-@printf " linking/verlinke %s to/zu %b%s%b ..." "$(OBJ)" $(blau) "$@" $(reset) >$(BA)
	-@df --output=ipcent / |tail -n1|grep - && $(SUDC)pkill postdrop;:
	-@man>$(KR);[ $$? -gt 1 ]&&{ sh configure inst _ man verbose;}||:;
	-@printf " (Version: %b%s%s%b\n " $(blau) "$$(cat versdt)" ")" $(reset) >$(BA)
	$(CC) $^ $(DEBUG)-o $@ $(LDFLAGS)
	-@ls .d/*.Td >$(KR) &&{ for datei in .d/*.Td; do mv -f $${datei} $${datei%.Td}.d; done;};:
	$(shell touch *.o $${EXEC})
	-@printf " Fertig mit/Finished with %b$(ICH)%b, Target: %b$@%b:, nachher/afterwords:\n" $(blau) $(reset) $(blau) $(reset)
	-@printf " '%b%s%b'\n" $(blau) "$$(ls -l --time-style=+' %d.%m.%Y %H:%M:%S' --color=always $(EXEC))" $(reset)

%.o : %.cpp
%.o : %.cpp $(DEPDIR)/%.d
	@[ $@ = $(DPROG).o ]&&{ $(call machvers);if test -f entwickeln; then awk "BEGIN {print `cat versdt`+0.00001}">versdt;\
	else printf " %bFile '%bentwickeln%b' missing, keeping the version number stable/ Datei '%bentwickeln%b' fehlt, lasse die Version gleich%b\n" \
	$(schwarz) $(grau) $(schwarz) $(grau) $(schwarz) $(reset) >$(BA); fi;}; :;
	@printf " kompiliere %b%s%b: " $(blau) "$<" $(reset) >$(BA);
#	-@if ! test -f instvz; then printf \"$$(getent passwd $$(logname)|cut -d: -f6)\">instvz; fi;
	-@if ! test -f instvz; then printf \"$$(pwd)\">instvz; fi; # wird in kons.cpp verwendet
	-$(CC) $(DEBUG)$(DEPFLAGS) $(CFLAGS) -c $< $(BFA);
	-@sed -i 's/versdt //g;s/gitvdt //g' $(DEPDIR)/*.Td
	-@if test -s fehler.txt; then vi +0/error fehler.txt; else rm -f fehler.txt; fi;
#	-@$(shell $(POSTCOMPILE))
	@if test -s fehler.txt; then false; fi;

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

.PHONY: compiler
compiler:
	@printf " Untersuche/Examining Compiler ...\n" >$(BA)
ifeq ('$(SPR)','')
$(warning Variable 'SPR' not assigned, please call './install.sh' before!)
$(error Variable 'SPR' nicht belegt, bitte vorher './install.sh' aufrufen!)
endif
	@[ "$(GCCOK)" = "1" ]||{ \
	[ "$(DISTR)" = "1" ]&&{ $(SUDC)add-apt-repository ppa:ubuntu-toolchain-r/test;$(SUDC)apt-get update;};:;\
	{ printf "Installiere/Installing Compiler ...\n" >$(BA);sh configure inst "$(CCInst)" "$(COMP)";:;};}
	-@[ "$(libmac)" ]&&{ for r in 1 2;do [ $$r = 1 ]&&{ lc="$(libmcd)";:;}||lc="$(libmc1d)";\
	[ -f /usr/include/mysql/mysql.h>$(KR) ]&& \
	find $$(find /usr -maxdepth 1 -type d -name "lib*" $(KF)|sort -r) -regextype egrep -regex ".*libm(ysql|ariadb)client.so" -print -quit $(KF)|\
	grep ''>$(KR)&& break;\
	sh configure inst _ "$$lc" verbose; done;}||:
	-@[ -z $$mitpg ]||$(SPR) $(pgd)>$(KR)||{ sh configure inst _ "$(pgd)" verbose;$(slc);};
# 3.5.17: auch libtiff5 hat gefehlt
	-@[ "$(LT)" ]&& for r in 1 2;do \
	[ $$r = 1 ]&& LTakt="$(LT)" ||{ [ -z "$(LT5)" ]&&break;LTakt="$(LT5)";};\
	find /usr/include /usr/local/include -name tiff.h -print -quit $(KF)|grep ''>$(KR)&&\
	find /usr/lib64 /usr/lib /usr/local/lib64 /usr/local/lib -maxdepth 2 -type l -xtype f -name "libtiff.so" -print -quit $(KF)|grep ''>$(KR)&& break;\
	sh configure inst _ "$$LTakt" verbose;\
	done; :;
#	P=tiff_copy;T=$$P.tar.gz;M=$$P-master;wget https://github.com/$(GITV)/$$P/archive/master.tar.gz -O $$T&&{ rm -rf $$P;tar xpvf $$T;} &&\
	mv $$M $$P&& cd $$P&&{ sed -i.bak s'/(thandle_t) client_data.fd);/(thandle_t) \&client_data.fd);/' tools/fax2tiff.c;\
	./configure&& make&& $(SUDC)make install&&$(SUDC)touch /usr/local/sclibtiff;\
	bef="cd `pwd`;make uninstall;cd -;";grep -q $$bef $(UNF)||printf "$$bef\n">>$(UNF);\
	$(SUDC)ldconfig;cd ..;};

	-@[ "$(LACL)" ]&&{ [ -f /usr/include/sys/acl.h ]|| sh configure inst _ "$(LACL)" verbose;}||:
	-@[ "$(LCURL)" ]&&{ [ -f /usr/include/curl/curl.h -o -f /usr/include/x86_64-linux-gnu/curl/curl.h ]|| sh configure inst _ "$(LCURL)" verbose;}||:
	-@[ "$(LBOOST)" ]&&{ $(SPR) $(LBOOST)>$(KR)|| sh configure inst _ "$(LBOOST)" verbose;}||:
	-@[ "$(LBIO)" ]&&{ $(SPR) "$(LBIO)">$(KR)||sh configure inst _ "$(LBIO)" verbose;}||:
	-@[ "$(LBLO)" ]&&{ $(SPR) "$(LBLO)">$(KR)||sh configure inst _ "$(LBLO)" verbose;}||:
#//	-@[ -f /usr/include/boost/iostreams/device/mapped_file.hpp -o -f /usr/share/doc/libboost-dev ]|| sh configure inst _ "$(LBOOST)" verbose;
# ggf. Korrektur eines Fehlers in libtiff 4.0.7, notwendig fuer hylafax+, 17.1.17 in Programm verlagert
	@printf "                                  \r" >$(BA)

.PHONY: stumm stumminst
stumm stumminst: BA::=/dev/null
stumm stumminst: BFA::=
stumm stumminst: rot::=""
stumm stumminst: blau::=""
stumm stumminst: gruen::=""
stumm stumminst: reset::=""

stumm: all

stumminst: install

$(INSTEXEC): $(EXEC)
	@printf " Copying program/ Kopiere Programmdatei: %b%s%b -> %b%s%b\n" $(blau) "$(EXEC)" $(reset) $(blau) "$(INSTEXEC)" $(reset) >$(BA)
	-@$(SUDC)pkill $(EXEC) $(KF); $(SUDC)pkill -9 $(EXEC) $(KF); $(SUDC)cp -p "$(EXEC)" "$(INSTEXEC)"

man_de.html: LGL::=deutsch
man_de.gz man_de.html: FKT::=FUNKTIONSWEISE
man_de.html: AWI::=AUSWIRKUNGEN
man_de.gz: OPN::=OPTIONEN

man_en.html: LGL::=english
man_en.gz man_en.html: FKT::=FUNCTIONALITY
man_en.html: AWI::=IMPLICATIONS
man_en.gz: OPN::=OPTIONS

.PHONY: install
install: $(INSTEXEC) $(INSTenMAN) $(INST_MAN) 

README.md: $(HTMLS)
	-@rm -f README.md
ifeq ("$(wildcard man_de)$(wildcard man_en)","man_deman_en")
	-@echo "<h3>Manual: 1) <a href=\"#english_E\">english</a>, 2) <a href=\"#deutsch_D\">deutsch (unten anschließend)</a></h3>" > README.md
endif
	@for d in $(MANS); do sed -n '20,$$p' $$d.html >> $@; [ -z $$A ]||A=$$A", ";A=$$A$(blau)$$d$(reset); done; \
	printf " %b$@%b neu erstellt aus: $$A\n" $(blau) $(reset)

define machvers	 
	VD="versdt";[ -f $$VD ]||echo 0.1>$$VD;:
endef

define priv_html
	-@printf " erstelle/generating:%b$(1)%b\n" $(blau) $(reset)
	-@groff -mandoc -Thtml -v >$(KR);EXC="$$$$?"; \
	for p in $(PGROFF); do { [ $$$${EXC} -gt 1 ]|| ! which groff>$(KR)|| ! $(SPR) $$$$p>$(KR);}&&{ sh configure inst _ $$$$p verbose;}; done; :;
	-@rm -f $(1).html
	-@sed -e 's/²gitv²/$(GITV)/g;s/²DPROG²/$(DPROG)/g;'\
	 -e 's/Ä/\&Auml;/g;s/Ö/\&Ouml;/g;s/Ü/\&Uuml;/g;s/ä/\&auml;/g;s/ö/\&ouml;/g;s/ü/\&uuml;/g;s/ß/\&szlig;/g;'\
	  $(1) | \
 	 groff -mandoc -Thtml -W break| \
	 sed -e "s/&amp;/\&/g;s@<h1 align=\".*\">man@<h1 align=\"center\">$(PROGGROSS) (Version $$$$(cat versdt)) - $$(LGL)<a name=\"$$(LGL)\"></a>@g;"\
	  -e "s/\(<a \(href\|name\)=\"[^\"]*\)/\1_D/g;/^<td width=/d;" > $(1).html
	@printf "%b%s%b neu aus %b%s%b erstellt\n" $(blau) "$(1).html" $(reset) $(blau) "$(1)" $(reset)
endef

# Aufruf des Programms mit -sh, um die Optionen in den manpages zu aktualisieren
# falls hier Berechtigungsfehler, dann z.B. home-Partion ohne exec
define manges
$(1).html: $(EXEC) $(1)
	$(call priv_html, $(1))
$(1).gz: $(EXEC) $(1) 
	-@printf " aktualisiere/updating %b$(1)%b\n" $(blau) $(reset)
	-@sed -i "s/\(Version \)[^\"]*/\1$$$$(cat versdt)/;s/\(\.TH[^\"]*\)\"[^\"]*/\1\"$$$$(date +'%d.%m.%y')/" $(1)
	-@Lang=$(shell echo $(1)|cut -d_ -f2|head -c1);\
		TMP=tmp_opt_$$$$Lang;chmod +x $(EXEC);\
		EX="./$(EXEC) -1lg $$$$Lang -sh";\
		W1="sed -e s/^/.br\n/;s/\\[[01]\\;3.m/\\\\fB/g;s/\\[0m/\\\\fR/g";\
		W1a=$$$$(echo $$$$W1|sed -e "s/"`printf \\\\033`"/\(ESC\)/g;s/\\\\n/\\\\\\\\n/g");\
		W2="sed :a;N;$$$$!ba";\
		printf " rufe auf/calling: '%b$$$$EX |$$$$W1a |$$$$W2 >$$$$TMP%b'\n" $(blau) $(reset);\
		$$$$EX|$$$$W1|$$$$W2>$$$$TMP; \
	 nlinit=`echo 'nl="'; echo '"'`; eval "$$$$nlinit"; \
	 von=".SH $$(OPN)"; bis=".SH $$(FKT)"; sed -i.bak "/$$$$von/,/$$$$bis/{/$$$$von/{n;p;r $$$$TMP$$$$nl};/$$$$bis/p;d}" $(1);
	@sed 's/²gitv²/$(GITV)/g;s/²DPROG²/$(DPROG)/g;s/\\fB/\\fI/g' $(1)|gzip -c >$$@
$(INST$(patsubst man_%,%,$(1))MAN): $(1).gz
	@$(SUDC)mkdir -p $$$$(dirname $$@)
	@printf " Copying Manual/ Kopiere Hilfedatei: %b%s%b -> %b%s%b\n" $(blau) "$(1)" $(reset) $(blau) "$$@" $(reset) >$(BA)
	@$(SUDC)cp -a $(1).gz $$@
endef
$(foreach prog,$(wildcard man_??),$(eval $(call manges,$(prog))))

.PHONY: fertig
fertig:

.PHONY: clean
clean: distclean fernclean

.PHONY: distclean
distclean: 
	@printf " Bereinige/Cleaning ...\n" >$(BA)
	@ZUL="$(EXEC) $(OBJ) .d/* $(HTMLS)";GEL=$$(ls -1 $$ZUL $(KF)|tr '\n' ' '); rm -f $$ZUL $(KF); \
	[ -z "$$(echo $$GEL|sed 's/ *$$//')" ]&&GEL="Hier/here: Nichts/nothing";printf " %b$$GEL%b geloescht/deleted!\n" $(blau) $(reset); 

.PHONY: fernclean
fernclean:
	@ZUL="$(INSTEXEC) $(INSTenMAN) $(INST_MAN)";GEL=$$($(SUDC)ls -1 $$ZUL $(KF)|tr '\n' ' '); $(SUDC)rm -f $$ZUL $(KF); \
	[ -z "$$(echo $$GEL|sed 's/ *$$//')" ]&&GEL="System: Nichts/nothing";printf " %b$$GEL%b geloescht/deleted!\n" $(blau) $(reset); 

.PHONY: confclean
confclean:
	-@sh -c 'D=$(INSTEXEC).conf;test -f $$D &&{ printf "Wollen Sie \"%b$$D%b\" wirklich loeschen (j/n)?" $(blau) $(reset); read answer; \
	if echo "$$answer"|grep -iq "^j\|^y";then $(SUDC)rm -r "$$D">$(KR)&&printf "\"%b%s%b\" geloescht!\n" $(blau) "$(INSTEXEC).conf" $(reset); fi;:;} \
	||{ printf "Konfigurationsdatei \"%b$$D%b\" fehlt.\n" $(blau) $(reset);}'

.PHONY: uninstall
uninstall: fernclean
	-@tac $(UNF)>tmp_$(UNROH)&& $(SUDC)blau=$(blau) reset=$(reset) bash tmp_$(UNROH);: # uninstallinv von hinten nach vorne abarbeiten
	-@[ "$(DISTR)" = "1" ]&&{ $(SUDC)apt-get -f install;};:;
	-@printf "Fertig mit uninstall!\n"

.PHONY: allesweg
allesweg: fernclean
	-@tac $(UNF)>tmp_$(UNROH)&& $(SUDC)blau=$(blau) reset=$(reset) bash tmp_$(UNROH) <<-EOF $'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n'$'\n' EOF;: # uninstallinv von hinten nach vorne abarbeiten
	-@[ "$(DISTR)" = "1" ]&&{ $(SUDC)apt-get -f install<<EOF $'\n'$'\n' EOF;};:;
	-@printf "Fertig mit uninstall!\n"

#//rufe:
#//	printf '$(UPR)$(PGROFF)\nprintf "$$blau%%s$$reset\\n" "$(UPR)$(PGROFF)"\n'>>gtest
#//	-@$(SUDC)blau=$(blau) reset=$(reset) sh gerufen

#//teste:
#//	sh -c 'VAR="lange\
#//	 Varible"; echo $$VAR'
#//	 echo $(GROFFCHECK)
#//	 @echo $(COMP)
#//	 @echo $(words $(COMP))
#//	 @printf "$$blau$(UREPO)$$reset\n"
#//	 for P in $(COMP); do echo $$P; VAR="$$P"; echo $$VAR; $(call uninst,$P) done
#//	 $(foreach VAR,$(COMP),echo $(VAR)\n)
#//	 @$(foreach VAR,$(COMP),$(call sunins,$(VAR),$(VAR)))
#//	$(foreach PG,$(COMP),$(call si_unins,$(PG),$(PG);$(UREPO)))
#//	 echo $(call uninst,$(COMP))
#//	$(SUDC)blau=$(blau) reset=$(reset) sh gtest

.PHONY: verschieb
verschieb:
	Z=../$(DPROG)rein;[ "$(LOESCH)" = "1" ]&&rm -rf $$Z;make all install&&\
		{ make transfer $$Z;{ cd $$Z;[ -d .git ]||make git;./configure;make version; cd - >$(KR);};}

.PHONY: vsneu
# geht nur, wenn das github-Repository vorher gelöscht ist
vsneu: LOESCH::=1
vsneu: verschieb

.PHONY: ruf
ruf:
	@$(EXPFAD)/$(EXEC)

.PHONY: rufv
rufv:
	@$(EXPFAD)/$(EXEC) -v

.PHONY: version
version: dovers
.PHONY: dovers
dovers: README.md
	@printf " Copying all files from/ Kopiere alle Dateien von: %b%s%b (Version %b%s%b) -> git (%b%s%b)\n" $(blau) "$(DPROG)" \
	$(reset) $(blau) $$(cat versdt) $(reset) $(blau) \
	"$$(F1=.git/FETCH_HEAD;test -f $$F1&&{ cut -f2-< $$F1|sed 's/^\s*//';:;}||cat .git/./config|sed -n '/url =/p')" $(reset) >$(BA) 
	-@cp -au Makefile Makefile.roh
	$(call setz_gitv,".")
	@git config --global push.default simple
	@git rm --cached --ignore-unmatch $(DTN) Makefile.roh vgb.cpp versdt README.md
	@git commit -m "Vor Version $$(cat versdt)"
	@git add $(GDAT:vgb.cpp=) versdt README.md 
	@git commit -m "Version $$(cat versdt)"
	@git push

FERTIG=$(error Fertig mit Transfer!)
TRS::=transfer
Ziel::=$(filter-out $(TRS),$(MAKECMDGOALS))
.PHONY: $(TRS)
$(TRS): dotrans
	$(FERTIG)
.PHONY: dotrans
dotrans:
	@# sed-Befehl: loesche alles zwischen /*// und */ (loesche einzeilige Muster(-zeilen), suche solche Abschnitte, loesche sonst leere erste und letzte Zeilen daraus, loesche Zwischenzeilen daraus, loesche Text vor und nach den Grenzen), loesche Zeilen mit //// am Anfang, loesche alles hinter ////
	@printf "Transfer nach %b$(Ziel)%b\n" $(blau) $(reset);\
	Start=1;\
	[ ! -d "$(Ziel)" ]&&{\
	 printf "Shall the directory %b$(Ziel)%b be created?/Soll das Verzeichnis %b$(Ziel)%b erstellt werden (y/j/n)? " $(blau) $(reset) $(blau) $(reset);\
	 read Antwort;\
	 [ $$Antwort = "y" -o $$Antwort = "j" ]&& mkdir -p $(Ziel);\
	};\
	[ -z "$(Ziel)" ]&&{ Start=0;:;}||[ ! -d "$(Ziel)" ]&& Start=0;\
	if [ $$Start = 0 ]; then\
	 printf "Makes a fair copy of the files of a github repository/ Kopiert Dateien eines github-Repositorys abzüglich mancher Kommentare ins Reine\n";\
	 printf "Synatax: %bmake $(TRS) \<zielverzeichnis\>%b\n" $(blau) $(reset);\
	 printf "Directory/Verzeichnis "%b$(Ziel)%b" nicht gefunden.\n" $(blau) $(reset);\
	 exit 1;\
	else\
	 ICH=transfer;\
	 . ./configure;\
	 for D in $$(find . -maxdepth 1 -name "*.cpp" -or -name "*.h"); do\
	  sed -e '/^[[:space:]]*\/\*\/\/.*\*\/[[:space:]]*$$/d;'\
		-e 's_/\*//[^*]*\*/__g;/\/\*\/\//,/\*\//{/^[[:space:]]*\/\*\/\//d;/\*\/[[:space:]]*$$/d;'\
		-e '/\/\*\/\//!{/\*\//!d};s_/\*//.*__;s_.*\*/__};/^[[:space:]]*\/\/\/\/.*/d;s_////.*__;s/\r$$//' $$D>$(Ziel)/$$D;\
		((DAT++));\
	  printf "$$blau$$D$$reset nach $$blau$(Ziel)/$$reset kopiert\n";\
	  chmod --reference=$$D $(Ziel)/$$D;\
	  chown --reference=$$D $(Ziel)/$$D;\
	 done;\
	 for D in .exrc Makefile install.sh man_?? versdt pname viall configure; do\
	  [ -f $$D ]&&{ sed '/^#\/\/.*/d;s_#\/\/.*__g' $$D>$(Ziel)/$$D;((DAT++));\
	   printf "$$blau$$D$$reset nach $$blau$(Ziel)/$$reset kopiert\n"; };\
	   chmod --reference=$$D $(Ziel)/$$D;\
	   chown --reference=$$D $(Ziel)/$$D;\
	  [ "$$D" = "Makefile" ]&&{\
	   ROH=$$D.roh; mv $(Ziel)/$$D $(Ziel)/$$ROH;\
	   printf "%b$(Ziel)/$$D%b in %b$(Ziel)/$$ROH/%b umbenannt\n" $(blau) $(reset) $(blau) $(reset);\
	  };\
	 done;\
	 echo $(DPROG)>$(Ziel)/pname;\
	 printf "Insgesamt $$blau$$DAT$$reset Dateien kopiert\n";\
	fi;
	@$(call setz_gitv,$(Ziel))
	@sh -c "cd $(Ziel);./configure; " && printf "%b./configure%b in %b$(Ziel)%b aufgerufen\n" $(blau) $(reset) $(blau) $(reset);\

.PHONY: newproj
newproj: neuproj
.PHONY: neuproj
neuproj:
	@Z=;while [ -z "$$Z" -o -d ../"$$Z" ]; do [ ! -z "$$Z" -a -d ../"$$Z" ]&& echo \'..\\"$$Z"\' gibt es schon/already exists.; echo Programmname/program name?; read Z;done;mkdir -p ../"$$Z";cp -ai kons.cpp kons.h DB.cpp DB.h Makefile .exrc configure install.sh man_?? viall* ../"$$Z";\
		sed -n ":Start;/\/\/α.*\/\/ω/{p;n;bStart};/\/\/α/,/\/\/ω/p;/VOMHAUPTCODE/i#include \"$$Z.h\"" "$(DPROG).cpp">"../$$Z/$$Z.cpp";\
    sed -n ":Start;/\/\/α.*\/\/ω/{p;n;bStart};/\/\/α/,/\/\/ω/p;1i#define DPROG \"$$Z\"" "$(DPROG).h">"../$$Z/$$Z.h";\
		M=man_de;K=KURZ;D=DEINST;[ -f $$M ]&&sed -n "1,/^\.SH $$K/p;/^\.SH $$K/,/^\.SH $$D/{/^\.SH $$K/d;/^\.SH /p};/^\.SH $$D/,\$${/^\.SH $$D/d;p}" $$M>../"$$Z"/$$M;\
		M=man_en;K=SHORT;D=UNINST;[ -f $$M ]&&sed -n "1,/^\.SH $$K/p;/^\.SH $$K/,/^\.SH $$D/{/^\.SH $$K/d;/^\.SH /p};/^\.SH $$D/,\$${/^\.SH $$D/d;p}" $$M>../"$$Z"/$$M;\
		cd ../"$$Z";\
		echo 0.1>versdt; touch entwickeln; echo $$Z>pname;\
		L="\"/var/log/\" DPROG \"vorgabe.log\"";\
		sh configure;\
		sed -i '/\$DTN [^'\'']/s/ +.* -pNu/ -pNu/' viall;\
		sed -i.bak '/\$DTN [^'\'']/s/\$DTN /\$DTN +'\''tabfirst|tab sview ..\/$(DPROG)\/$(DPROG).cpp|tabnext|tab sview ..\/$(DPROG)\/$(DPROG).h|tabfirst'\'' /' viall;\
		sh viall;\
		echo Weiter mit/Go on with: \"cd ../"$$Z"\";


-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))
