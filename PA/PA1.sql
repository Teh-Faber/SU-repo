create database PA1;
use PA1;
show databases;

delete from produktsalg;
delete from salg;
delete from kunde;

create table produkt (
  produkt_id int not null,
  navn char(25) not null,
  pris int not null,
  primary key (produkt_id)
); 

create table dag (
  dag_id int not null,
  ugedag char(25) not null,
  vejr char(25) not null,
  temperatur int not null,
  primary key(dag_id)
);


create table ekspedient (
  ekspedient_id int not null,
  navn char(25) not null,
  primary key(ekspedient_id)
);

create table kunde (
  kunde_id int not null,
  navn char(25) not null,
  primary key(kunde_id)
);

create table salg (
  salg_id int not null,
  dag_id int not null,
  ekspedient_id int not null,
  kunde_id int not null,
  primary key(salg_id),
  foreign key (dag_id) references dag(dag_id),
  foreign key (ekspedient_id) references ekspedient(ekspedient_id),  
  foreign key (kunde_id) references kunde(kunde_id)
);

create table produktsalg (
  produktsalg_id int not null,
  salg_id int not null,
  produkt_id int not null,
  primary key(produktsalg_id),
  foreign key (salg_id) references salg(salg_id),
  foreign key (produkt_id) references produkt(produkt_id)
);

insert into ekspedient values
 (1,'James'),
 (2,'Jonny'),
 (3,'Josefine');
 
insert into kunde values
 (1,'Mikkel'),
 (2,'Søren'),
 (3,'Anders'),
 (4,'Emil'),
 (5,'Frederik'),
 (6,'Kasper');

insert into produkt values
 (1,'Flødeis', 45),
 (2,'Slik', 15),
 (3,'Sodavandsis', 10),
 (4,'Kage', 50),
 (5,'Toast', 100),
 (6,'Banan', 5),
 (7,'Kaffe', 25);
 
insert into dag values
 (1,'Mandag', 'Regn', 16),
 (2,'Tirsdag', 'Solskin', 21),
 (3,'Onsdag', 'Regn', 7),
 (4,'Torsdag', 'Regn', 10),
 (5,'Fredag', 'Solskin', 21),
 (6,'Lørdag', 'Solskin', 23),
 (7,'Søndag', 'Regn', 11);
 
insert into salg values
 (1,1,1,5),
 (2,2,2,1),
 (3,3,3,2),
 (4,4,1,3),
 (5,5,2,1),
 (6,1,3,5),
 (7,2,1,1),
 (8,3,1,6),
 (9,4,1,3),
 (10,5,1,5),
 (11,1,1,2),
 (12,2,2,5),
 (13,3,2,3),
 (14,4,2,2),
 (15,5,2,1);

insert into produktsalg values
 (1,2,1),
 (2,2,1),
 (3,2,3),
 (4,5,3),
 (5,5,3),
 (6,5,1),
 (7,5,1),
 (8,5,2),
 (9,1,2),
 (10,2,4),
 (11,3,5),
 (12,4,6),
 (13,5,7),
 (14,6,1),
 (15,7,2),
 (16,8,3),
 (17,9,4),
 (18,10,5),
 (19,11,6),
 (21,12,7),
 (22,13,1),
 (23,14,2),
 (24,15,3),
 (25,11,4),
 (26,12,5),
 (27,13,6),
 (28,14,7),
 (29,15,1);
 
 
-- Opgave 1: Vis navnet på alle produkter der koster under eller præcist gennemsnits prisen for produkter.
select navn 
	from produkt 
	where pris <= (select avg(pris) from produkt);

-- Opgave 2: Udregn den samlede indtjening for alle produktsalg.
select sum(p.pris)
	from salg 				as s
	inner join produktsalg 	as ps 	on s.salg_id = ps.salg_id
	inner join produkt 		as p 	on ps.produkt_id = p.produkt_id;

-- Opgave 3: Vis ugedag for de dage hvor der ikke har været nogle salg.
select ugedag
	from dag
	where dag_id not in (select dag_id from salg);

-- Opgave 4: Vis navnet på den ekspedient der har solgt for flest penge.
select e.navn, sum(p.pris)
	from ekspedient 		as e
	inner join salg 		as s	on e.ekspedient_id = s.ekspedient_id 
	inner join produktsalg 	as ps 	on s.salg_id = ps.salg_id
	inner join produkt 		as p 	on ps.produkt_id = p.produkt_id
	group by e.navn
	order by sum(p.pris) desc
	limit 1;
                                
-- Opgave 5: Vis navnet på den kunde der har købt flest is, og hvor mange is der er købt.
select k.navn, count(ps.produktsalg_id)
	from kunde 				as k
	inner join salg 		as s 	on k.kunde_id = s.kunde_id
	inner join produktsalg 	as ps 	on s.salg_id = ps.salg_id
	where ps.produkt_id in (select produkt_id from produkt where navn like "%is%")
	group by k.navn
	order by count(ps.produktsalg_id) desc
	limit 1;

-- Opgave 6: Vis hvor stort beløb hver kunde har købt for, i rækkefølge mindst til størst.
select k.navn, sum(p.pris)
	from kunde 				as k
	inner join salg 		as s	on k.kunde_id = s.kunde_id
	inner join produktsalg 	as ps 	on s.salg_id = ps.salg_id
	inner join produkt 		as p 	on ps.produkt_id = p.produkt_id
	group by k.navn
	order by sum(p.pris) asc;

-- Opgave 7: Vis den samlede indtjening for hver ugedag.
select d.ugedag, sum(p.pris)
	from salg 				as s
	inner join produktsalg 	as ps 	on s.salg_id = ps.salg_id
	inner join produkt 		as p 	on ps.produkt_id = p.produkt_id
	inner join dag 			as d 	on s.dag_id = d.dag_id
	group by d.ugedag;

-- Opgave 8: For hvert salg kan der være tilknyttet flere produktsalg. Vis gennemsnits temperaturen for alle de salg hvor der indgår mindst et produktsalg af is.
select avg(temperatur)
	from dag as d
	inner join( select s.dag_id
				from salg 				as s
				inner join produktsalg 	as ps 	on s.salg_id = ps.salg_id
				inner join produkt 		as p 	on ps.produkt_id = p.produkt_id
				where ps.produkt_id in (select produkt_id from produkt where navn like "%is%")
				group by s.salg_id
			  ) as s_is 	on d.dag_id = s_is.dag_id;

-- Opgave 9: Grundet GDPR skal alle kunde navne fjernes, lav en kommando der sætter alle kunde navne til 'Ukendt'. Bemærk denne kommando skal køres til sidst og der gives intent resultat.
SET sql_safe_updates = 0;
	update kunde 
	set	navn = "Ukendt";

select navn
from kunde;