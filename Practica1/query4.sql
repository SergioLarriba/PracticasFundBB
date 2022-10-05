SELECT orders.ordernumber, count(orderdetails.quantityordered)
FROM offices,orders join orderdetails on orders.ordernumber=orderdetails.ordernumber
Group by orders.ordernumber
order by count(orderdetails.quantityordered) desc limit 1