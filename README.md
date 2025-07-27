# 🎓 Student Management System (Qt + PostgreSQL)

A clean, modular, hand-coded GUI application built with Qt Creator (CMake-based) using `QWidget` and `PostgreSQL` for database storage (to be configured later). This system is designed to manage users, teachers, students, marks, and basic authentication.

---

## 📁 Folder Structure

```

/StudentManagementSystem
- │
- ├── CMakeLists.txt
- ├── main.cpp
- ├── mainwindow\.cpp
- ├── mainwindow\.h
- │
- ├── login/
- │   ├── login.cpp
- │   └── login.h
- │
- ├── admin/
- │   ├── admin.cpp            # Admin panel – manages teachers
- │   └── admin.h
- │
- ├── student/
- │   ├── student.cpp          # Displays student information
- │   ├── student.h
- │
- ├── marks/
- │   ├── marks.cpp            # Manages student marks
- │   ├── marks.h
- │
- ├── db/
- │   └── database.cpp         # PostgreSQL connection logic (will implement later)
- │   └── database.h
- │
- └── README.md

```

---

## ✅ Features

- Manual login system (admin/student)
- Admin dashboard: manage teachers
- Marks dashboard: record and update student marks
- PostgreSQL backend (to be integrated after GUI is complete)
- No drag-and-drop: all GUI is **hard-coded** using QWidget-based layout code for precision and clarity

---

## 🛠️ Tech Stack

- Qt Creator (Widgets)
- CMake
- C++17
- PostgreSQL (for later use)

---

## 🚀 How to Run

1. Open Qt Creator
2. Select **Open Project** and choose `CMakeLists.txt`
3. Build and Run the app (`Ctrl + R`)
4. PostgreSQL setup will be configured after UI is complete

---

## 📌 Status

- [x] Folder structure finalized
- [x] UI base classes created
- [ ] PostgreSQL integration (pending)
- [ ] Full authentication
- [ ] Final polish and deployment

---

## 🧠 Developer Notes

> “Avoid drag-and-drop. Stick to hard-coded layouts for clean, aligned UI.”

- Use `QVBoxLayout`, `QGridLayout`, `QHBoxLayout`, etc., directly in `.cpp` files
- Avoid cluttering one file — separate components by logical function
- PostgreSQL setup will be delayed until all forms and flows are working visually

---

## 🔧 PostgreSQL (To-Do Later)

When ready:
- Use `QSqlDatabase` with PostgreSQL driver (`QPSQL`)
- Add credentials and queries in `database.cpp`
- Set up tables: users, students, marks

---

## 🧪 Example Screens (Coming Soon)

> Screenshots of:
- Login screen
- Admin dashboard
- Student view
- Marks entry

---

## 📋 License

MIT – free for educational and personal use.
```

---




