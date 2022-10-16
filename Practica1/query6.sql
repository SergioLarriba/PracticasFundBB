select 
	id1.productcode as id1, id2.productcode as id2, count(id1.ordernumber) as carros
from 
	orderdetails id1 join orderdetails id2 on id1.ordernumber=id2.ordernumber
where 
	id1.productcode <> id2.productcode and id1.productcode < id2.productcode
group by
	id1.productcode, id2.productcode
having count(id1.ordernumber) > 1
order by id1.productcode, id2.productcode
