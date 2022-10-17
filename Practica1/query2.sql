select 
	p.productline, Avg(o.shippeddate - o.orderdate) as dif 
from 
	orders o join orderdetails orderdi on o.ordernumber=orderdi.ordernumber
	join products p on p.productcode=orderdi.productcode 
group by 
	p.productline
order by 
	dif desc
