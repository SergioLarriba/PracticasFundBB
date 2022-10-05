-- Query4
-- hago una tabla con los productos y las unidades 
with quant as (select p.productcode, o.quantityordered, o.ordernumber from orderdetails as o join products
			  as p on o.productcode=p.productcode), 
	-- hago un subconjunto que una la tabla offices con la tabla orderdetails
	joins as (select o.officecode, orderd.productcode 
			 from offices o join employees e on o.officecode=e.officecode --offices-employees
			 join customers cust on e.employeenumber=cust.salesrepemployeenumber --employees-customers
			 join orders ord on cust.customernumber=ord.customernumber --customers-orders
			 join orderdetails orderd on ord.ordernumber=orderd.ordernumber --orders-orderdetails
			 )

select sum(quant.quantityordered),joins.officecode
from quant join joins on quant.productcode=joins.productcode 
group by joins.officecode
order by sum(quant.quantityordered) desc
