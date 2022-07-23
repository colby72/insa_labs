SELECT employee_name FROM works
WHERE salary>(SELECT max(salary) FROM works WHERE company_name='Small Bank Corporation')
