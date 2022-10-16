-- x es la tabla que contiene la diferencia de cada pedido de shipeddate - orderdate
with x as (select (ord.shippeddate-ord.orderdate) as time from orders ord)

select 
	pr.productline, count(x.time)
from 
	products pr, x
group by pr.productline
order by count(x.time) desc
