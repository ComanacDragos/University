package ro.ubb.catalog.service;

import ro.ubb.catalog.domain.Student;
import ro.ubb.catalog.domain.validators.ValidatorException;
import ro.ubb.catalog.repository.Repository;

import java.util.HashSet;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

/**
 * @author radu.
 */
public class StudentService {
    private Repository<Long, Student> repository;

    public StudentService(Repository<Long, Student> repository) {
        this.repository = repository;
    }

    public void addStudent(Student student) throws ValidatorException {
        repository.save(student);
    }

    public Set<Student> getAllStudents() {
        Iterable<Student> students = repository.findAll();
        return StreamSupport.stream(students.spliterator(), false).collect(Collectors.toSet());
    }

    /**
     * Returns all students whose name contain the given string.
     * 
     * @param s
     * @return
     */
    public Set<Student> filterStudentsByName(String s) {
        Iterable<Student> students = repository.findAll();
        //version 1
//        Set<Student> filteredStudents = StreamSupport.stream(students.spliterator(), false)
//                .filter(student -> student.getName().contains(s)).collect(Collectors.toSet());

        //version 2
        Set<Student> filteredStudents= new HashSet<>();
        students.forEach(filteredStudents::add);
        filteredStudents.removeIf(student -> !student.getName().contains(s));

        return filteredStudents;
    }
}
