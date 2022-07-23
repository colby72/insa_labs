/* Activation du support pour FOREIGN KEY */
PRAGMA foreign_keys=ON;

/*
Brain storm avec le on cascade ...
*/

create table employee (
	employee_name VARCHAR(50) PRIMARY KEY,
	street VARCHAR(50),
	city VARCHAR(50)
);

create table works (
	employee_name VARCHAR(50) PRIMARY KEY,
	company_name VARCHAR(50),
	salary REAL,
	FOREIGN KEY (employee_name) REFERENCES employee(employee_name),
	FOREIGN KEY (company_name) REFERENCES company(company_name)
);

create table company (
	company_name VARCHAR(50) PRIMARY KEY,
	city VARCHAR(50)
);

create table manages (
	employee_name VARCHAR(50) PRIMARY KEY,
	manager_name VARCHAR(50),
	FOREIGN KEY (employee_name) REFERENCES employee(employee_name),
	FOREIGN KEY (manager_name) REFERENCES employee(employee_name)	
);


insert into company values('First Bank Corporation','New York');
insert into company values('Small Bank Corporation','New York');
insert into company values('Dream Corporation','Paris');

insert into employee values('Jones',"47 RATA STREET",'New York');
insert into employee values('Mark','47 RATA STREET','New York');
insert into employee values('Jhon','68-70 TIRAU STREET','Paris');
insert into employee values('Paul','13, rue de Pfastatt','Marseille');
insert into employee values('Dupont','80, rue de la lolalilpa','Bordeaux');


insert into works values ('Jones','First Bank Corporation',10000);
insert into works values ('Mark','First Bank Corporation',2000);
insert into works values ('Jhon','Small Bank Corporation',8000);
insert into works values ('Paul','Dream Corporation',40000);
insert into works values ('Dupont','Small Bank Corporation',6000);

insert into manages values('Mark','Jones');
