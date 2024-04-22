show databases;
Create database Lektion3_Sejlads;
Use Lektion3_Sejlads;

create table omraade (
  omraade_id int not null,
  navn char(25) not null,
  primary key (omraade_id)
); 

create table havn (
  havn_id int not null,
  navn char(25) not null,
  omraade_id int not null,
  primary key (havn_id),
  foreign key (omraade_id) references omraade(omraade_id) 
);

create table baadejer(
  baadejer_id int not null,
  navn char(25) not null,
  primary key (baadejer_id)  
);

create table baad(
  baad_id int not null,
  navn char(25) not null,
  baadtype char(25) not null,
  baadejer_id int not null,
  hjemme_havn int not null,
  primary key (baad_id),
  foreign key (baadejer_id) references baadejer(baadejer_id),
  foreign key (hjemme_havn) references havn(havn_id)
);

create table sejltur(
  sejltur_id int not null,
  dato date not null,
  varighed int not null,
  baad_id int not null,
  fra_havn int not null,
  til_havn int not null, 
  primary key (sejltur_id),
  foreign key (baad_id) references baad(baad_id),
  foreign key (fra_havn) references havn(havn_id),
  foreign key (til_havn) references havn(havn_id)	
);

insert into omraade values
 (1,'Fyn'),
 (2,'Samsø'),
 (3,'Ærø');
 
insert into havn values
 (1,'bogense',1),
 (2,'kerteminde',1),
 (3,'svendborg',1),
 (4,'faaborg',1),
 (5,'ballen',2),
 (6,'sælvig',2),
 (7,'langør',2),
 (8,'Søby',3),
 (9,'Marstal',3),
 (10,'Ærøskøbing',3);

insert into baadejer values
 (1,'aage jensen'),
 (2,'Torben schmidt'),
 (3,'Henriette Nielsen'),
 (4,'Poul sørensen'),
 (5,'Hedvig jensen'),
 (6,'Villads holm'),
 (7,'Erik Pedersen'),
 (8,'Svendborg Bådudlejning');
 
insert into baad values
 (1,'aage Måge','Drabant 27',1,1),
 (2,'elviras fryd','Banner 30',8,3),
 (3,'jenny','trimaran',2,2),
 (4,'havlit','hvilling',8,3),
 (5,'marianne','X-99',3,4),
 (6,'neptun','folkebåd',4,5),
 (7,'Sgt. pepper','Ylva',5,6),
 (8,'Fremad','ylva',6,7),
 (9,'Lydia','Bianca 28',7,9),
 (10,'leonora','lm24',6,10);

insert into sejltur values
 (1,'2021-04-18',6,1,1,2),
 (2,'2020-09-23',4,2,7,1),
 (3,'2021-07-12',3,3,10,4),
 (4,'2019-06-18',8,4,4,6),
 (5,'2018-10-23',1,5,9,10),
 (6,'2021-07-14',9,6,7,8),
 (7,'2020-05-16',5,7,3,2),
 (8,'2017-09-24',4,8,6,5),
 (9,'2021-06-19',5,9,1,4),
 (10,'2020-04-12',2,10,10,3),
 (11,'2021-08-09',3,1,3,4),
 (12,'2020-08-01',6,2,7,3),
 (13,'2020-04-23',4,3,4,1),
 (14,'2021-07-02',3,4,9,4),
 (15,'2021-07-03',8,5,4,1);
 
 
 -- q1:Lav en liste over navnene på de både, som er anløbet Ballen i september måned. Navnet "Ballen" må hardkodes i forespørgslen, men ikke dens id (5).
 select b.navn
 from baad as b
 join sejltur as s on b.baad_id = s.baad_id
 join havn as h on s.til_havn = h.havn_id
 where h.navn = 'Ballen';
 
 -- Q2:Vis navnene på de bådejere som ikke har været ude at sejle.
 select be.navn
 from baadejer as be
 join baad as b on b.baadejer_id = be.baadejer_id
 where b.baad_id not in (select baad_id from sejltur); 
 
 -- Q3:udskriv navnet på den havn, som har flest hjemmehørende både.
 select h.navn
 from havn as h
 join baad as b on h.havn_id = b.hjemme_havn
 group by h.havn_id, h.navn
 order by COUNT(b.hjemme_havn) DesC
 limit 1;
 
 -- Q4: lav en oversigt over samtlige sejladser indeholdende bådens navn, dato, varighed, navnet på fra-havnen og navnet på til-havnen. Det er tilladt at hardkode antallet af rækker i sejltur-tabellen i forespørgslen.
 select b.navn 'Båd navn', s.dato 'dato', s.varighed 'Varighed', hf.navn 'fra havn', ht.navn 'til havn'
 from sejltur as s
 join baad as b on s.baad_id = b.baad_id
 join havn as hf on s.fra_havn = hf.havn_id
 join havn as ht on s.til_havn = ht.havn_id
 order by s.dato desc;
 
 -- Q5:lav en liste over navnene samtlige områder med angivelse af antal have pr område.
 select o.navn 'Område Navn', count(h.omraade_id) 'Antal havne'
 from omraade as o
 join havn as h on o.omraade_id = h.omraade_id
 group by o.navn;
 
 select * from sejltur inner join havn on sejltur.fra_havn = havn.havn_id where havn.navn = 'Marstal';

 
 -- Lektion 4 øvelser:
 select count(*) as antal, month(dato) as maaned
 from sejltur
 where fra_havn not in 
 (select havn.havn_id from havn where havn.navn = 'Marstal')
 group by month(dato)
 order by count(*) desc, month(dato) desc;
 
 
