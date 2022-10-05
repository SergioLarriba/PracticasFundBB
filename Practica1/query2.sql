

Select p.productline, count(x.time) 
FROM (select(ord.shippeddate-ord.orderdate) as time FROM orders as ord)as x,products as p, orders as ord
 
WHERE time=ord.shippeddate-ord.orderdate
Group by p.productline
order by count(x.time)