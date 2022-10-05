with officenosale_group as(select ordernumber FROM orders WHERE shippeddate IS NULL and orderdate>='2003-01-01' and orderdate<='2003-12-31')
SELECT o.country, count(o.officecode)
FROM offices as o, orders as ord
WHERE ord.ordernumber in (select* FROM officenosale_group)
GRoup by o.country
having count(o.officecode) >=1
order by count(o.officecode) desc 