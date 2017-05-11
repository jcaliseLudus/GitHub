-- Classement des clients par nombre d'occupations --

SELECT T_CLIENT.CLI_ID, T_CLIENT.CLI_NOM, T_CLIENT.CLI_PRENOM, (COUNT(T_FACTURE.CLI_ID) AS CLI_NBRESA
FROM T_CLIENT, T_FACTURE
WHERE T_CLIENT.CLI_ID = T_FACTURE.CLI_ID
GROUP BY T_CLIENT.CLI_ID
ORDER BY CLI_NBRESA DESC;

-- Classement des clients par montant dépensé dans l'hôtel -- 

SELECT T_CLIENT.CLI_ID, T_CLIENT.CLI_NOM, T_CLIENT.CLI_PRENOM, (COUNT(TJ_CHB_TRF.TRF_CHB_PRIX) / TJ_CHB__PLN_CLI.CHB_PLN_CLI_NB_PERS)  AS MONTANTTOTAL
FROM T_CLIENT, T_FACTURE, TJ_CHB_TRF, TJ_CHB__PLN_CLI
WHERE T_CLIENT.CLI_ID = T_FACTURE.CLI_ID
AND T_CLIENT.CLI_ID = TJ_CHB__PLN_CLI.CLI_ID
AND SUBSTR(TJ_CHB_TRF.TRF_DATE_DEBUT,0,6) = SUBSTR(T_FACTURE.FAC_DATE,0,6)
GROUP BY T_CLIENT.CLI_ID
ORDER BY MONTANTTOTAL DESC;

-- Classement des occupations par mois --

SELECT PLN_JOUR, COUNT(CHB_PLN_CLI_OCCUPE) AS CHB_NB_OCCUPATION
FROM TJ_CHB__PLN_CLI
WHERE CHB_PLN_CLI_OCCUPE = 1
GROUP BY STRFTIME('%m', PLN_JOUR)

--Classement des occupations par trimestre

SELECT COUNT(CHB_PLN_CLI_OCCUPE) AS CHB_NB_OCCUPATION
FROM TJ_CHB__PLN_CLI
WHERE CHB_PLN_CLI_OCCUPE = 1
GROUP BY STRFTIME('%m', PLN_JOUR, '+2 months')

-- Montant TTC de chaque ligne de facture ( avec remises)

SELECT T_FACTURE.FAC_ID,  T_FACTURE.CLI_ID,  T_FACTURE.FAC_DATE, (T_LIGNE_FACTURE.LIF_MONTANT * (1 + (LIF_REMISE_POURCENT / 100))) AS TOTALTTC
FROM T_FACTURE, T_LIGNE_FACTURE, TJ_CHB_TRF
WHERE T_FACTURE.FAC_ID = T_LIGNE_FACTURE.FAC_ID
GROUP BY T_FACTURE.FAC_ID



-- Vous vous créez en tant que client de l'hôtel -- 

INSERT INTO T_CLIENT(TIT_CODE, CLI_NOM, CLI_PRENOM)
VALUES ('M.', 'CALISE', 'Julien');
INSERT INTO T_ADRESSE(CLI_ID, ADR_LIGNE1, ADR_LIGNE2, ADR_LIGNE3, ADR_LIGNE, ADR_CP, ADR_VILLE)
VALUES (101, "11 Rue de L'Anneau",'""','""';'""', '"67200"', '"STRASBOURG"');

--ne pas oublier vos moyens de communications --

INSERT INTO T_TELEPHONE(CLID_ID, TYP_CODE, TEL_NUMERO, TEL_LOCALISATION)
VALUES(101, 'GSM', '06-59-13-57-75','""');

--Vous créez une nouvelle chambre à la date du jour --

INSERT INTO T_CHAMBRE(CHB_NUMERO, CHB_ETAGE, CHB_BAIN, CHB_DOUCHE, CHB_WC, CHB_COUCHAGE, CHB_POSTE_TEL)
VALUES (22,'2e', 1, 1, 1, 1, '121');
INSERT INTO TJ_CHB__PLN_CLI(CHB_ID, CLI_ID, PLN_JOUR, CHB_PLN_CLI_NB_PERS, CHB_PLN_CLI_RESERVE, CHB_PLN_CLI_OCCUPE)
VALUES (22, 101, '"2017-05-11"', 3, 1,0);

-- Vous serez 3 occupants et souhaitez le maximum de confort pour cette chambre dont le prix est 30% superieur à la chambre la plus cher --

INSERT INTO TJ_CHB_TRF(CHB_ID, TRF_DATE_DEBUT, TRF_CHB_PRIX)
VALUES (22, '"2017-05-11"', 665);

-- Le réglement de votre facture sera effectué en CB --

INSERT INTO T_FACTURE(CLI_ID, PMT_CODE, FAC_DATE, FAC_PMT_DATE)
VALUES (101, '"CB"', '"2017-05-11"', '"2017-05-13' );

-- Une seconde facture a été éditée car le tarif a changé : rabais de 10 % --

INSERT INTO T_LIGNE_FACTURE(FAC_ID, LIF_QTE, LIF_REMISE_POURCENT)
VALUES (2375,1, 10);