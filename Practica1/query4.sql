select 
	o.officecode, sum(orderdi.quantityordered)
from 
	orderdetails orderdi natural join orders 
	natural join customers c 
	join employees e natural join offices o on c.salesrepemployeenumber=e.employeenumber 
group by 
	o.officecode
order by sum(orderdi.quantityordered) desc limit 1
