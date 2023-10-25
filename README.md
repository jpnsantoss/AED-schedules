# Projeto AED

## Lesson
- `start` (double)
- `end` (double)
- `type` (string)
- `weekday` (string)
## UcClass
- `ucCode` (string)
- `classCode` (string)
- `lessons` (list of Lesson objects)
- `capacity` (int)
- `studentsNumber` (int)

## Student
- `studentCode` (string)
- `studentName` (string)
- `ucClasses` (list of UcClass objects)

## Dataset
- `students` (set of Student objects)
- `ucClasses` (vector of UcClass objects)
- `requests` (queue of Request objects)
- `history` (queue of Request objects)

## Request
- `student` (Student object)
- `removeAdd` (map of UcClass objects to UcClass objects)
