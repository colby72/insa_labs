SELECT e.employee_name, e.city
FROM employee AS e, works AS w
WHERE w.company_name='First Bank Corporation' AND e.employee_name=w.employee_name
