SELECT e.employee_name, e.street, e.city
FROM employee AS e, works AS w
WHERE w.salary>10000 AND e.employee_name=w.employee_name
