USE projet_fin_annee

INSERT INTO CALENDRIER VALUE ('24-10-04');
INSERT INTO CALENDRIER VALUE ('24-10-05');

INSERT INTO CLIENT VALUES 
	(1, 'Tolotra', 'H', 'Soatsiadino', '+261383529356'),
	(2, 'Sarobidy', 'H', 'Ivory Atsimo', '+261340429457'),
	(3, 'Caddy', 'H', 'Tanambao', '+261388049531'),
	(4, 'Fytah', 'H', 'Ampbalapary', '+261387330400'),
	(5, 'Brayanno', 'H', 'Ankodona', '+261343775597'),
	(6, 'Hermann', 'H', 'Soatsiadino', '+261345240845');

INSERT INTO RESERVATION VALUES
	(1, 1, 1, '24-10-04', '24-10-04', 50000, 0, 1),
	(2, 1, 2, '24-10-05', '24-10-05', 50000, 0, 1),
	(3, 1, 3, '24-10-05', '24-10-05', 50000, 0, 2),
	(4, 1, 4, '24-10-05', '24-10-05', 50000, 0, 3),
	(5, 1, 5, '24-10-04', '24-10-04', 50000, 0, 2),
	(6, 1, 6, '24-10-04', '24-10-04', 50000, 0, 3);