select 
	customers.customernumber,customers.customername,sum(payments.amount) 
from
	products natural join orderdetails natural join orders natural join customers natural join payments
where 
	products.productname = '1940 Ford Pickup Truck'
group by 
	customers.customernumber
order by 
	sum(payments.amount) desc
