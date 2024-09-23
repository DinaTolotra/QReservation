DROP DATABASE IF EXISTS projet_fin_annee;

CREATE DATABASE IF NOT EXISTS projet_fin_annee;
USE projet_fin_annee;
# -----------------------------------------------------------------------------
#       TABLE : VEHICULE
# -----------------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS VEHICULE
 (
   NUMVEH INTEGER(1) NOT NULL AUTO_INCREMENT  ,
   NBPLACE INTEGER(2) NOT NULL  ,
   NBPLACEDISPO INTEGER(2) NOT NULL  
   , PRIMARY KEY (NUMVEH) 
 ) 
 comment = "";

# -----------------------------------------------------------------------------
#       TABLE : CLIENT
# -----------------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS CLIENT
 (
   NUMCLI INTEGER(2) NOT NULL AUTO_INCREMENT  ,
   NOM CHAR(32) NOT NULL  ,
   SEXE CHAR(1) NOT NULL  ,
   ADRESSE CHAR(32) NULL  ,
   TEL CHAR(13) NOT NULL  
   , PRIMARY KEY (NUMCLI) 
 ) 
 comment = "";

# -----------------------------------------------------------------------------
#       TABLE : CALENDRIER
# -----------------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS CALENDRIER
 (
   DATEDEPART DATE NOT NULL  
   , PRIMARY KEY (DATEDEPART) 
 ) 
 comment = "";

# -----------------------------------------------------------------------------
#       TABLE : RESERVATION
# -----------------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS RESERVATION
 (
   NUMRES INTEGER(2) NOT NULL AUTO_INCREMENT  ,
   NUMVEH INTEGER(1) NOT NULL  ,
   NUMCLI INTEGER(2) NOT NULL  ,
   DATEDEPART DATE NOT NULL  ,
   DATERES DATE NOT NULL  ,
   FRAISTOTAL INTEGER(6) NOT NULL  ,
   AVANCE INTEGER(6) NULL  ,
   NUMPLACE INTEGER(2) NOT NULL  
   , PRIMARY KEY (NUMRES) 
 ) 
 comment = "";

# -----------------------------------------------------------------------------
#       INDEX DE LA TABLE RESERVATION
# -----------------------------------------------------------------------------


CREATE  INDEX I_FK_RESERVATION_VEHICULE
     ON RESERVATION (NUMVEH ASC);

CREATE  INDEX I_FK_RESERVATION_CLIENT
     ON RESERVATION (NUMCLI ASC);

CREATE  INDEX I_FK_RESERVATION_CALENDRIER
     ON RESERVATION (DATEDEPART ASC);


# -----------------------------------------------------------------------------
#       CREATION DES REFERENCES DE TABLE
# -----------------------------------------------------------------------------


ALTER TABLE RESERVATION 
  ADD FOREIGN KEY FK_RESERVATION_VEHICULE (NUMVEH)
      REFERENCES VEHICULE (NUMVEH) ;


ALTER TABLE RESERVATION 
  ADD FOREIGN KEY FK_RESERVATION_CLIENT (NUMCLI)
      REFERENCES CLIENT (NUMCLI) ;


ALTER TABLE RESERVATION 
  ADD FOREIGN KEY FK_RESERVATION_CALENDRIER (DATEDEPART)
      REFERENCES CALENDRIER (DATEDEPART) ;

