with product_name as (select productname from products where productname='1940 Ford Pickup Truck')
SELECT customers.customername,customers.customernumber,payments.amount 
FROM payments join customers on customers.customernumber=payments.customernumber, products
where products.productname in (select * from product_name)
order by payments.amount desc