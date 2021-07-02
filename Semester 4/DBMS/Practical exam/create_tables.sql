use PracticalExam
go

create table CoffeShops(
	id int primary key identity(1, 1),
	name varchar(100),
	address varchar(100)
)

create table Categories(
	id int primary key identity(1, 1),
	name varchar(100),
	description varchar(100)
)

create table CoffeProducts(
	id int primary key identity(1, 1),
	name varchar(100),
	categoryId int references Categories(id)
)

create table Customers(
	id int primary key identity(1, 1),
	name varchar(100)
)

create table FavouriteCoffeProducts(
	customerId int foreign key references Customers(id),
	coffeProductId int foreign key references CoffeProducts(id),
	primary key(customerId, coffeProductId)
)

create table ShopProducts(
	shopId int foreign key references CoffeShops(id),
	coffeProductId int foreign key references CoffeProducts(id),
	price int
	primary key (shopId, coffeProductId)
)

create table Orders(
	id int primary key identity(1, 1),
	customerId int foreign key references Customers(id),
	shopId int,
	coffeProductId int,
	orderDatetime datetime,
	foreign key (shopId, coffeProductId) references ShopProducts(shopId, coffeProductId)
)

insert into Categories (name, description) VALUES
('n1', 'd1'),
('n2', 'd1'),
('n3', 'd2'),
('n4', 'd2')

select * from Categories
select * from CoffeProducts
