create table familie (
  familie_id int not null,
  navn char(50) not null,
  latinsknavn char(50) not null,
  primary key (familie_id)
); 

create table fugl (
  fugl_id int not null,
  navn char(50) not null,
  latinsknavn char(50) not null,
  familie_id int not null,
  primary key(fugl_id),
  foreign key (familie_id) references familie(familie_id)
);

create table lokation(
  lokation_id int not null,
  navn char(40) not null,
  primary key (lokation_id)
);

create table observation(
  observation_id int not null,
  dato date not null,
  antal int not null,	
  lokation_id int not null,
  fugl_id int not null,
  primary key (observation_id),
  foreign key (lokation_id) references lokation(lokation_id),
  foreign key (fugl_id) references fugl(fugl_id)
);

insert into familie values
 (1,'Kragefugle','Corvidae'),
 (2,'Brokfugle','Charadriidae'),
 (3,'Mejser','Paridae');
insert into fugl values
 (1,'Skovskade','Garralus glandarius',1),
 (2,'Allike','Corvus monedula',1),
 (3,'Vibe','Vanellus vanellus',2),
 (4,'Stor præstekrave','Charadrius hiaticula',2),
 (5,'Musvit','Parus major',3),
 (6,'Blåmejse','Cyanistes caeruleus',3);
insert into lokation values
 (1,'Enebærodde'),
 (2,'Knudshoved'),
 (3,'Vresen'),
 (4,'Gamborg Fjord'),
 (5,'Fyns Hoved');
insert into observation values
 (1,'2014-10-18',7,2,2),
 (2,'2012-09-23',64,5,3),
 (3,'1996-02-01',1,1,1),
 (4,'2002-11-17',7,3,4),
 (5,'2018-12-29',5,1,6); 
 
 -- Q1: Vis navnene på de fugle som er blevet observeret på lokationen Vresen.
 select fugl.navn 
 from observation 
 join fugl on fugl.fugl_id = observation.fugl_id
 join lokation on lokation.lokation_id = observation.lokation_id
 where lokation.navn = 'Vresen';
 
 -- Q2:Vis det samlede observerede antal fugle, som tilhører familien brokfugle.
 select sum(antal) 
 from familie 
 join fugl on familie.familie_id = fugl.familie_id 
 join observation on observation.fugl_id = fugl.fugl_id 
 where familie.navn = 'brokfugle';
 
 -- Q3:Vis navnene på de fugle, som er blevet observeret i december måned.Hvert navn må kun forekomme én gang.
 select fugl.navn
 from fugl
 join observation on observation.fugl_id = fugl.fugl_id
 where 12 = month(dato);

-- Q4:Vis navnene på de lokationer, hvor der er observeret fugle af familien corvidae.
 select l.navn  
 from familie as ff 
 join fugl as f on ff.familie_id = f.familie_id   
 join observation as o on o.fugl_id = f.fugl_id  
 join lokation as l on l.lokation_id = o.lokation_id 
 where ff.latinsknavn = 'Corvidae';
 
-- Q5:Vis datoen for databasens ældste observation.
 select min(dato)
 from observation;

-- Q6:Vis navnene på de lokationer, som ikke har observationer.
 select l.navn
 from lokation as l 
 where lokation_id not in (select lokation_id from observation);


