with director as (select employees.employeenumber from employees where employees.reportsto IS NULL),
	 report_group as (select employees.employeenumber from employees where employees.reportsto in (select * from director))

select
	employees.employeenumber, employees.lastname
FROM 
	employees
WHERE 
	employees.reportsto IN (select * from report_group)
