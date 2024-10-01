USE projet_fin_annee

DELETE FROM RESERVATION;
DELETE FROM CALENDRIER;
DELETE FROM CLIENT;
DELETE FROM VEHICULE;

INSERT INTO CALENDRIER VALUE
	('24-10-04');

INSERT INTO VEHICULE VALUES
	(1, 3),
	(2, 18),
	(3, 18);

INSERT INTO CLIENT VALUES 
	(1, 'Tolotra', 'H', 'Soatsiadino', '+261383529356'),
	(2, 'Sarobidy', 'H', 'Ivory Atsimo', '+261340429457'),
	(3, 'Caddy', 'H', 'Tanambao', '+261388049531'),
	(4, 'Fytah', 'H', 'Ampbalapary', '+261387330400'),
	(5, 'Brayanno', 'H', 'Ankodona', '+261343775597'),
	(6, 'Hermann', 'H', 'Soatsiadino', '+261345240845');

INSERT INTO RESERVATION VALUES
	(1, 1, 1, '24-10-04', '24-10-04', 50000, 0, 1),
	(2, 1, 1, '24-10-04', '24-10-04', 50000, 0, 2);
