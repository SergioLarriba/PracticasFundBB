-- tabla con las oficinas que no han realizado ninguna venta durante el año 2003 (shippeddate is null)
with no_sale_offices as (select o.officecode from offices o natural join employees natural join customers natural join orders ord where ord.shippeddate is NULL and orderdate>='2003-01-01' and orderdate<='2003-12-31')

select 
	o.country, count(o.officecode) as offices_with_no_sales
from 
	offices o
where 
	o.officecode in (select * from no_sale_offices)
group by 
	o.country
having count(o.officecode)>=1
order by count(o.officecode) desc 
