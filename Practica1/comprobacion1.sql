SELECT products.productname, payments.amount
FROM customers join payments on customers.customernumber=payments.customernumber, products
WHERE customers.customername='Herkku Gifts' and products.productname='1940 Ford Pickup Truck'