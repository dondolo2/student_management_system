#include "database.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QRandomGenerator>

void Database::connectAndInitialize() {
    // Set up the PostgreSQL database connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

    // Configure connection parameters - adjust these for your environment
    db.setHostName("localhost");
    db.setPort(5432);
    db.setDatabaseName("school_management");
    db.setUserName("postgres");
    db.setPassword("yourpassword"); // Change to your PostgreSQL password

    // Open the database connection
    if (!db.open()) {
        qDebug() << "❌ Database failed to open:" << db.lastError().text();
        return;
    }

    qDebug() << "✅ Database connected successfully to PostgreSQL";

    createTables();
}

void Database::createTables() {
    QSqlQuery query;

    // Enable foreign key constraints
    query.exec("SET CONSTRAINTS ALL DEFERRED");

    // === Create Courses Table ===
    query.exec("CREATE TABLE IF NOT EXISTS courses ("
               "id SERIAL PRIMARY KEY,"
               "name TEXT NOT NULL)");

    // === Create Modules Table ===
    query.exec("CREATE TABLE IF NOT EXISTS modules ("
               "id SERIAL PRIMARY KEY,"
               "name TEXT NOT NULL,"
               "year INTEGER NOT NULL CHECK (year BETWEEN 1 AND 3),"
               "course_id INTEGER REFERENCES courses(id) ON DELETE CASCADE)");

    // === Create Students Table ===
    query.exec("CREATE TABLE IF NOT EXISTS students ("
               "id SERIAL PRIMARY KEY,"
               "name TEXT NOT NULL,"
               "year INTEGER NOT NULL CHECK (year BETWEEN 1 AND 3),"
               "course_id INTEGER REFERENCES courses(id) ON DELETE SET NULL)");

    // === Create Lecturers Table ===
    query.exec("CREATE TABLE IF NOT EXISTS lecturers ("
               "id SERIAL PRIMARY KEY,"
               "name TEXT NOT NULL)");

    // === Create Lecturer-Modules Mapping Table ===
    query.exec("CREATE TABLE IF NOT EXISTS lecturer_modules ("
               "lecturer_id INTEGER REFERENCES lecturers(id) ON DELETE CASCADE,"
               "module_id INTEGER REFERENCES modules(id) ON DELETE CASCADE,"
               "PRIMARY KEY (lecturer_id, module_id))");

    // === Create Marks Table ===
    query.exec("CREATE TABLE IF NOT EXISTS marks ("
               "student_id INTEGER REFERENCES students(id) ON DELETE CASCADE,"
               "module_id INTEGER REFERENCES modules(id) ON DELETE CASCADE,"
               "mark REAL CHECK (mark BETWEEN 0 AND 100),"
               "PRIMARY KEY (student_id, module_id))");

    qDebug() << "✅ All tables created successfully with proper constraints.";
}

void Database::populateSampleData() {
    insertCourses();
    insertModules();
    insertLecturers();
    assignLecturersToModules();
    insertStudents();
    assignMarks();

    qDebug() << "✅ Sample data populated in PostgreSQL database.";
}

void Database::insertCourses() {
    QSqlQuery query;
    QStringList courseNames = {
        "Computer Science", "Electrical Engineering", "Linguistics",
        "Agricultural Science", "Chartered Accounting", "Theology"
    };

    query.prepare("INSERT INTO courses (name) VALUES (?)");

    for (const QString& name : courseNames) {
        query.addBindValue(name);
        if (!query.exec()) {
            qDebug() << "Error inserting course:" << query.lastError().text();
        }
    }
}

void Database::insertModules() {
    QSqlQuery query;

    // Map of course names to their IDs
    QMap<QString, int> courseIds;
    QSqlQuery idQuery("SELECT id, name FROM courses");
    while (idQuery.next()) {
        courseIds[idQuery.value(1).toString()] = idQuery.value(0).toInt();
    }

    // Module data - course name, year, module name
    QList<QList<QVariant>> modules = {
        // Computer Science
        {"Computer Science", 1, "Programming Fundamentals (Python)"},
        {"Computer Science", 1, "Discrete Mathematics"},
        {"Computer Science", 1, "Computer Systems & Architecture"},
        {"Computer Science", 1, "Introduction to Databases"},
        {"Computer Science", 1, "Web Development Basics (HTML/CSS/JS)"},
        {"Computer Science", 1, "Algorithms & Problem Solving"},
        {"Computer Science", 1, "Academic Writing for Tech"},

        {"Computer Science", 2, "Data Structures & Algorithms"},
        {"Computer Science", 2, "Operating Systems"},
        {"Computer Science", 2, "Software Engineering Principles"},
        {"Computer Science", 2, "Computer Networks"},
        {"Computer Science", 2, "Object-Oriented Design (Java/C++)"},
        {"Computer Science", 2, "Human-Computer Interaction (HCI)"},
        {"Computer Science", 2, "Technical Communication"},

        {"Computer Science", 3, "Artificial Intelligence Fundamentals"},
        {"Computer Science", 3, "Machine Learning Basics"},
        {"Computer Science", 3, "Cybersecurity Essentials"},
        {"Computer Science", 3, "Cloud Computing (AWS/Azure)"},
        {"Computer Science", 3, "Mobile App Development"},
        {"Computer Science", 3, "Capstone Project I"},
        {"Computer Science", 3, "Ethics in Computing"},

        // Electrical Engineering
        {"Electrical Engineering", 1, "Circuit Theory & Analysis"},
        {"Electrical Engineering", 1, "Digital Electronics"},
        {"Electrical Engineering", 1, "Engineering Mathematics I"},
        {"Electrical Engineering", 1, "Electromagnetism Basics"},
        {"Electrical Engineering", 1, "Technical Drawing & CAD"},
        {"Electrical Engineering", 1, "Introduction to Programming (C)"},
        {"Electrical Engineering", 1, "Workshop Practice"},

        {"Electrical Engineering", 2, "Signals & Systems"},
        {"Electrical Engineering", 2, "Microprocessors & Embedded Systems"},
        {"Electrical Engineering", 2, "Power Systems I"},
        {"Electrical Engineering", 2, "Control Systems"},
        {"Electrical Engineering", 2, "Analog Electronics"},
        {"Electrical Engineering", 2, "Engineering Mathematics II"},
        {"Electrical Engineering", 2, "Industrial Training"},

        {"Electrical Engineering", 3, "Renewable Energy Systems"},
        {"Electrical Engineering", 3, "IoT & Smart Devices"},
        {"Electrical Engineering", 3, "Power Electronics"},
        {"Electrical Engineering", 3, "Robotics & Automation"},
        {"Electrical Engineering", 3, "Project Management for Engineers"},
        {"Electrical Engineering", 3, "Capstone Project II"},
        {"Electrical Engineering", 3, "Professional Ethics in Engineering"},

        // Linguistics
        {"Linguistics", 1, "Introduction to Linguistics"},
        {"Linguistics", 1, "Phonetics & Phonology"},
        {"Linguistics", 1, "Morphology & Syntax"},
        {"Linguistics", 1, "Academic Writing for Linguists"},
        {"Linguistics", 1, "Sociolinguistics Basics"},
        {"Linguistics", 1, "Language Acquisition"},
        {"Linguistics", 1, "Research Methods I"},

        {"Linguistics", 2, "Semantics & Pragmatics"},
        {"Linguistics", 2, "Historical Linguistics"},
        {"Linguistics", 2, "Psycholinguistics"},
        {"Linguistics", 2, "Computational Linguistics"},
        {"Linguistics", 2, "Field Methods in Linguistics"},
        {"Linguistics", 2, "Bilingualism & Multilingualism"},
        {"Linguistics", 2, "Research Methods II"},

        {"Linguistics", 3, "Discourse Analysis"},
        {"Linguistics", 3, "Language Documentation"},
        {"Linguistics", 3, "Neurolinguistics"},
        {"Linguistics", 3, "Applied Linguistics (TESOL)"},
        {"Linguistics", 3, "Forensic Linguistics"},
        {"Linguistics", 3, "Thesis Project I"},
        {"Linguistics", 3, "Ethics in Linguistic Research"},

        // Agricultural Science
        {"Agricultural Science", 1, "Introduction to Soil Science"},
        {"Agricultural Science", 1, "Crop Production I"},
        {"Agricultural Science", 1, "Animal Husbandry Basics"},
        {"Agricultural Science", 1, "Agricultural Economics"},
        {"Agricultural Science", 1, "Farm Machinery & Tools"},
        {"Agricultural Science", 1, "Agroecology"},
        {"Agricultural Science", 1, "Communication Skills for Agric"},

        {"Agricultural Science", 2, "Plant Pathology"},
        {"Agricultural Science", 2, "Livestock Management"},
        {"Agricultural Science", 2, "Irrigation & Water Management"},
        {"Agricultural Science", 2, "Agricultural Biotechnology"},
        {"Agricultural Science", 2, "Agribusiness Management"},
        {"Agricultural Science", 2, "Pest & Disease Control"},
        {"Agricultural Science", 2, "Research Methods in Agriculture"},

        {"Agricultural Science", 3, "Sustainable Farming Practices"},
        {"Agricultural Science", 3, "Food Security & Policy"},
        {"Agricultural Science", 3, "Precision Agriculture"},
        {"Agricultural Science", 3, "Agri-Entrepreneurship"},
        {"Agricultural Science", 3, "Climate-Smart Agriculture"},
        {"Agricultural Science", 3, "Capstone Project III"},
        {"Agricultural Science", 3, "Agricultural Ethics"},

        // Chartered Accounting
        {"Chartered Accounting", 1, "Financial Accounting I"},
        {"Chartered Accounting", 1, "Business Mathematics"},
        {"Chartered Accounting", 1, "Microeconomics"},
        {"Chartered Accounting", 1, "Business Communication"},
        {"Chartered Accounting", 1, "Introduction to Taxation"},
        {"Chartered Accounting", 1, "Commercial Law"},
        {"Chartered Accounting", 1, "IT for Accountants"},

        {"Chartered Accounting", 2, "Managerial Accounting"},
        {"Chartered Accounting", 2, "Macroeconomics"},
        {"Chartered Accounting", 2, "Auditing Principles"},
        {"Chartered Accounting", 2, "Corporate Finance"},
        {"Chartered Accounting", 2, "Taxation II"},
        {"Chartered Accounting", 2, "Business Statistics"},
        {"Chartered Accounting", 2, "Ethics in Accounting"},

        {"Chartered Accounting", 3, "Advanced Financial Reporting"},
        {"Chartered Accounting", 3, "Strategic Management"},
        {"Chartered Accounting", 3, "Forensic Accounting"},
        {"Chartered Accounting", 3, "International Finance"},
        {"Chartered Accounting", 3, "Public Sector Accounting"},
        {"Chartered Accounting", 3, "Professional Practice"},
        {"Chartered Accounting", 3, "Capstone Case Studies"},

        // Theology
        {"Theology", 1, "Introduction to Old Testament"},
        {"Theology", 1, "New Testament Survey"},
        {"Theology", 1, "Church History I"},
        {"Theology", 1, "Systematic Theology I"},
        {"Theology", 1, "Hermeneutics"},
        {"Theology", 1, "World Religions"},
        {"Theology", 1, "Academic Writing for Theology"},

        {"Theology", 2, "Biblical Greek/Hebrew"},
        {"Theology", 2, "Christian Ethics"},
        {"Theology", 2, "Homiletics (Preaching)"},
        {"Theology", 2, "Pastoral Counseling"},
        {"Theology", 2, "Missiology"},
        {"Theology", 2, "Church History II"},
        {"Theology", 2, "Research Methods in Theology"},

        {"Theology", 3, "Apologetics"},
        {"Theology", 3, "Contemporary Theology"},
        {"Theology", 3, "Leadership in Ministry"},
        {"Theology", 3, "Theology of Worship"},
        {"Theology", 3, "Capstone Thesis"},
        {"Theology", 3, "Interfaith Dialogue"},
        {"Theology", 3, "Social Justice & Theology"}
    };

    query.prepare("INSERT INTO modules (name, year, course_id) VALUES (?, ?, ?)");

    for (const auto& module : modules) {
        QString courseName = module[0].toString();
        int courseId = courseIds.value(courseName, -1);

        if (courseId == -1) {
            qDebug() << "Course not found:" << courseName;
            continue;
        }

        query.addBindValue(module[2].toString()); // module name
        query.addBindValue(module[1].toInt());     // year
        query.addBindValue(courseId);              // course_id

        if (!query.exec()) {
            qDebug() << "Error inserting module:" << query.lastError().text();
        }

        query.finish();
    }
}

void Database::insertLecturers() {
    QSqlQuery query;

    // Group lecturers by course
    QMap<QString, QStringList> courseLecturers = {
        {"Computer Science", {
                                 "Prof. Kwame Osei", "Dr. Amina Diallo", "Prof. Naledi Mbatha",
                                 "Dr. Tunde Adebayo", "Prof. Ifeoma Chukwu", "Dr. Jabari Okonjo",
                                 "Ms. Zara Mbeki"
                             }},
        {"Electrical Engineering", {
                                       "Dr. Sipho Dlamini", "Dr. Aisha Bello", "Dr. Femi Okafor",
                                       "Dr. Nia Johnson", "Dr. Thabo Molefe", "Dr. Lindiwe Ngcobo",
                                       "Prof. Samuel Adeyemi"
                                   }},
        {"Linguistics", {
                            "Dr. Oluwaseun Adebayo", "Prof. Amahle Dlamini", "Dr. Kofi Mensah",
                            "Dr. Ezekiel Okeke", "Prof. Rajesh Patel", "Dr. Priya Sharma",
                            "Dr. Nomsa Khumalo"
                        }},
        {"Agricultural Science", {
                                     "Prof. Arun Kumar", "Dr. Ananya Reddy", "Prof. Vikram Joshi",
                                     "Dr. Meera Iyer", "Mr. Rohan Desai", "Dr. Sanjay Gupta",
                                     "Dr. Rahul Mehta"
                                 }},
        {"Chartered Accounting", {
                                     "Dr. Kavita Srinivasan", "Dr. Anika Verma", "Dr. Aarav Deshpande",
                                     "Prof. Deepika Rajan", "Dr. Rishi Kapoor", "Ms. Ananya Iyer",
                                     "Dr. Vikram Choudhary"
                                 }},
        {"Theology", {
                         "Rev. Swami Anand Mishra", "Prof. Johan van der Merwe",
                         "Dr. Elsie Pretorius", "Prof. Hendrik Botha", "Dr. Marike van Niekerk",
                         "Ms. Anika Venter", "Mr. Lukas de Wet"
                     }}
    };

    query.prepare("INSERT INTO lecturers (name) VALUES (?)");

    for (const auto& lecturers : courseLecturers) {
        for (const QString& name : lecturers) {
            query.addBindValue(name);
            if (!query.exec()) {
                qDebug() << "Error inserting lecturer:" << query.lastError().text();
            }
            query.finish();
        }
    }
}

void Database::assignLecturersToModules() {
    QSqlQuery query;

    // Get all modules grouped by course and year
    query.exec("SELECT m.id, c.name, m.year FROM modules m "
               "JOIN courses c ON m.course_id = c.id "
               "ORDER BY c.name, m.year, m.id");

    QMap<QString, QMap<int, QList<int>>> courseYearModules;
    while (query.next()) {
        int moduleId = query.value(0).toInt();
        QString courseName = query.value(1).toString();
        int year = query.value(2).toInt();

        courseYearModules[courseName][year].append(moduleId);
    }

    // Get all lecturers grouped by course
    QMap<QString, QList<int>> courseLecturers;
    query.exec("SELECT l.id, c.name FROM lecturers l "
               "JOIN (SELECT id, name, ROW_NUMBER() OVER () as rn FROM lecturers) l2 ON l.id = l2.id "
               "JOIN (SELECT name, (ROW_NUMBER() OVER () - 1) / 7 as course_idx FROM courses) c "
               "ON l2.rn / 7 = c.course_idx");

    while (query.next()) {
        int lecturerId = query.value(0).toInt();
        QString courseName = query.value(1).toString();
        courseLecturers[courseName].append(lecturerId);
    }

    // Assign 3 modules to each lecturer in their course
    query.prepare("INSERT INTO lecturer_modules (lecturer_id, module_id) VALUES (?, ?)");

    for (const QString& courseName : courseYearModules.keys()) {
        const QList<int>& lecturers = courseLecturers.value(courseName);
        const QMap<int, QList<int>>& yearModules = courseYearModules.value(courseName);

        for (int year : yearModules.keys()) {
            const QList<int>& modules = yearModules.value(year);

            // Distribute modules among lecturers
            for (int i = 0; i < modules.size(); i++) {
                int lecturerIndex = i % lecturers.size();
                int lecturerId = lecturers[lecturerIndex];
                int moduleId = modules[i];

                query.addBindValue(lecturerId);
                query.addBindValue(moduleId);

                if (!query.exec()) {
                    qDebug() << "Error assigning lecturer to module:" << query.lastError().text();
                }
                query.finish();
            }
        }
    }
}

void Database::insertStudents() {
    QSqlQuery query;

    // Map of course names to their IDs
    QMap<QString, int> courseIds;
    QSqlQuery idQuery("SELECT id, name FROM courses");
    while (idQuery.next()) {
        courseIds[idQuery.value(1).toString()] = idQuery.value(0).toInt();
    }

    // Student data - course name, year, student name
    QList<QList<QVariant>> students = {
        // Computer Science Year 1
        {"Computer Science", 1, "Bakang Sechele"},
        {"Computer Science", 1, "Mankoko Mokone"},
        {"Computer Science", 1, "Lungelo Ntuli"},
        {"Computer Science", 1, "Harish Pillai"},
        {"Computer Science", 1, "Rohan Desai"},
        {"Computer Science", 1, "Refilwe Mothapo"},
        {"Computer Science", 1, "Wei Chen"},
        {"Computer Science", 1, "Amit Banerjee"},
        {"Computer Science", 1, "Fezekile Tshabalala"},
        {"Computer Science", 1, "Zhi Yuan"},
        {"Computer Science", 1, "Kabelo Mothapo"},
        {"Computer Science", 1, "Sihle Gamedze"},
        {"Computer Science", 1, "Timbilu Nkosi"},
        {"Computer Science", 1, "Ntombizodwa Ndebele"},
        {"Computer Science", 1, "Vutivi Baloyi"},
        {"Computer Science", 1, "Thato Kgosi"},
        {"Computer Science", 1, "Mpumelelo Ndlovu"},
        {"Computer Science", 1, "Tiyani Chauke"},

        // Computer Science Year 2
        {"Computer Science", 2, "Nomvula Mthembu"},
        {"Computer Science", 2, "Thabo Mokoena"},
        {"Computer Science", 2, "Nomalanga Nyoni"},
        {"Computer Science", 2, "Marike van Niekerk"},
        {"Computer Science", 2, "Zanele Mbatha"},
        {"Computer Science", 2, "Mthokozisi Shabangu"},
        {"Computer Science", 2, "Zwivhuya Tshikudo"},
        {"Computer Science", 2, "Buhle Xaba"},
        {"Computer Science", 2, "Keneilwe Mahlase"},
        {"Computer Science", 2, "Koketso Mothapo"},
        {"Computer Science", 2, "Hlengeleti Mathebula"},
        {"Computer Science", 2, "Mpho Tshikororo"},
        {"Computer Science", 2, "Qaqambile Matroshe"},
        {"Computer Science", 2, "Kgotso Mothapo"},
        {"Computer Science", 2, "Keneilwe Rasebotsa"},
        {"Computer Science", 2, "Ontiretse Mothibe"},
        {"Computer Science", 2, "Yan Guo"},
        {"Computer Science", 2, "Jabulani Zulu"},
        {"Computer Science", 2, "Thato Mothapo"},

        // Computer Science Year 3
        {"Computer Science", 3, "Lufuno Nemadzivha"},
        {"Computer Science", 3, "Swati Menon"},
        {"Computer Science", 3, "Masego Letsholo"},
        {"Computer Science", 3, "Adriaan Vosloo"},
        {"Computer Science", 3, "Sikhanyiso Nkomo"},
        {"Computer Science", 3, "Siyabonga Mthembu"},
        {"Computer Science", 3, "Xongile Mhlongo"},
        {"Computer Science", 3, "Pulane Motaung"},
        {"Computer Science", 3, "Mankwe Mothibe"},
        {"Computer Science", 3, "Lesego Mothapo"},
        {"Computer Science", 3, "Vuyani Mafu"},
        {"Computer Science", 3, "Mthokozisi Zwane"},
        {"Computer Science", 3, "Mandla Mkhize"},
        {"Computer Science", 3, "Lerato Mothapo"},
        {"Computer Science", 3, "Ndzalama Ndlovu"},
        {"Computer Science", 3, "Mandla Mfenyana"},
        {"Computer Science", 3, "Vutlhari Mabasa"},
        {"Computer Science", 3, "Lindelwa Tsabedze"},

        // Electrical Engineering Year 1
        {"Electrical Engineering", 1, "Nomsa Mlotshwa"},
        {"Electrical Engineering", 1, "Fhumulani Tshikovhele"},
        {"Electrical Engineering", 1, "Annemarie Kruger"},
        {"Electrical Engineering", 1, "Rhandzeka Mabuza"},
        {"Electrical Engineering", 1, "Sandile Ndlovu"},
        {"Electrical Engineering", 1, "Sibusiso Motsa"},
        {"Electrical Engineering", 1, "Masechaba Motsamai"},
        {"Electrical Engineering", 1, "Rahul Gupta"},
        {"Electrical Engineering", 1, "Willem de Klerk"},
        {"Electrical Engineering", 1, "Nomsa Matsebula"},
        {"Electrical Engineering", 1, "Mei Zhang"},
        {"Electrical Engineering", 1, "Christiaan van Staden"},
        {"Electrical Engineering", 1, "Tshimangadzo Makhuvha"},
        {"Electrical Engineering", 1, "Tshepo Mokwena"},
        {"Electrical Engineering", 1, "Jabulani Mkhize"},
        {"Electrical Engineering", 1, "Theunis Fourie"},
        {"Electrical Engineering", 1, "Sasekani Moyana"},
        {"Electrical Engineering", 1, "Andile Gqoba"},

        // Electrical Engineering Year 2
        {"Electrical Engineering", 2, "Mandla Nkala"},
        {"Electrical Engineering", 2, "Esona Mdingi"},
        {"Electrical Engineering", 2, "Khanyiso Mxenge"},
        {"Electrical Engineering", 2, "Tumelo Ntshingila"},
        {"Electrical Engineering", 2, "Buhle Shongwe"},
        {"Electrical Engineering", 2, "Nomcebo Dlamini"},
        {"Electrical Engineering", 2, "Tebello Makhanya"},
        {"Electrical Engineering", 2, "Petronella van Rensburg"},
        {"Electrical Engineering", 2, "Priya Sharma"},
        {"Electrical Engineering", 2, "Nhlanhla Maluleke"},
        {"Electrical Engineering", 2, "Ndivhuwo Muthambi"},
        {"Electrical Engineering", 2, "Tshimangadzo Netshivhale"},
        {"Electrical Engineering", 2, "Hlamarisa Baloyi"},
        {"Electrical Engineering", 2, "Rui Jiang"},
        {"Electrical Engineering", 2, "N'wamitwa Mhlongo"},
        {"Electrical Engineering", 2, "Mudzunga Tshikovhele"},
        {"Electrical Engineering", 2, "Tebogo Mothapo"},
        {"Electrical Engineering", 2, "Zukisa Nongogo"},

        // Electrical Engineering Year 3
        {"Electrical Engineering", 3, "Unathi Mtya"},
        {"Electrical Engineering", 3, "Nosipho Zwane"},
        {"Electrical Engineering", 3, "Sanjay Gupta"},
        {"Electrical Engineering", 3, "Ntombizodwa Dlamini"},
        {"Electrical Engineering", 3, "Elsie Pretorius"},
        {"Electrical Engineering", 3, "Thandeka Dube"},
        {"Electrical Engineering", 3, "Tebatso Mothiba"},
        {"Electrical Engineering", 3, "Xin Dong"},
        {"Electrical Engineering", 3, "Sunita Kapoor"},
        {"Electrical Engineering", 3, "Zwivhuya Nkuna"},
        {"Electrical Engineering", 3, "Thulani Cele"},
        {"Electrical Engineering", 3, "Bongani Ndlovu"},
        {"Electrical Engineering", 3, "Ntshengedzeni Mphaphuli"},
        {"Electrical Engineering", 3, "Sipho Magagula"},
        {"Electrical Engineering", 3, "N'wamitwa Nxumalo"},
        {"Electrical Engineering", 3, "Preeti Naidoo"},
        {"Electrical Engineering", 3, "Aletta van Jaarsveld"},
        {"Electrical Engineering", 3, "Qi Song"},
        {"Electrical Engineering", 3, "Tshegofatso Mothapo"},

        // Continue with other courses and years...
        // (Additional student data would be added here following the same pattern)
    };

    query.prepare("INSERT INTO students (name, year, course_id) VALUES (?, ?, ?)");

    for (const auto& student : students) {
        QString courseName = student[0].toString();
        int courseId = courseIds.value(courseName, -1);

        if (courseId == -1) {
            qDebug() << "Course not found:" << courseName;
            continue;
        }

        query.addBindValue(student[2].toString()); // student name
        query.addBindValue(student[1].toInt());    // year
        query.addBindValue(courseId);              // course_id

        if (!query.exec()) {
            qDebug() << "Error inserting student:" << query.lastError().text();
        }

        query.finish();
    }
}

void Database::assignMarks() {
    QSqlQuery query;

    // Get all students with their course_id
    query.exec("SELECT s.id, s.year, s.course_id FROM students s");

    while (query.next()) {
        int studentId = query.value(0).toInt();
        int year = query.value(1).toInt();
        int courseId = query.value(2).toInt();

        // Get all modules for this student's course and year
        QSqlQuery moduleQuery;
        moduleQuery.prepare("SELECT id FROM modules WHERE course_id = ? AND year = ?");
        moduleQuery.addBindValue(courseId);
        moduleQuery.addBindValue(year);
        moduleQuery.exec();

        while (moduleQuery.next()) {
            int moduleId = moduleQuery.value(0).toInt();
            float mark = QRandomGenerator::global()->bounded(40, 100); // 40–100%

            QSqlQuery markQuery;
            markQuery.prepare("INSERT INTO marks (student_id, module_id, mark) VALUES (?, ?, ?)");
            markQuery.addBindValue(studentId);
            markQuery.addBindValue(moduleId);
            markQuery.addBindValue(mark);

            if (!markQuery.exec()) {
                qDebug() << "Error inserting mark:" << markQuery.lastError().text();
            }
        }
    }
}
