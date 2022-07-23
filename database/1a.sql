PRAGMA foreign_keys=on;

CREATE TABLE IF NOT EXISTS employee(
	employee_name varchar(255),
	street varchar(255),
	city varchar(255),
	primary key (employee_name)
	);

CREATE TABLE IF NOT EXISTS company(
	company_name varchar(255),
	city varchar(255),
	primary key (company_name)
	);

CREATE TABLE IF NOT EXISTS works(
	employee_name varchar(255),
	company_name varchar(255),
	salary real,
	primary key (employee_name),
	foreign key (employee_name) references employee,
	foreign key (company_name) references company
	);

CREATE TABLE IF NOT EXISTS manages(
	employee_name varchar(255),
	manager_name varchar(255),
	primary key (employee_name),
	foreign key (employee_name) references employee,
	foreign key (manager_name) references employee
	);
