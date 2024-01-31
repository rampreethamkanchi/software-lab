import tkinter as tk
from tkinter import messagebox
import pickle
import re
import os


class Person:

  def __init__(self, name, email, password):
    self.name = name
    self.email = email
    self.password = password


class Teacher(Person):

  def __init__(self, name, email, password, subject):
    super().__init__(name, email, password)
    self.subject = subject


class UGStudent(Person):

  def __init__(self, name, email, password, roll_number, department):
    super().__init__(name, email, password)
    self.roll_number = roll_number
    self.department = department


class PGStudent(Person):

  def __init__(self, name, email, password,roll_number, specialization):
    super().__init__(name, email, password)
    self.roll_number = roll_number
    self.specialization = specialization


class MainClass:

  def __init__(self, root):
    self.root = root
    self.root.geometry("500x500")  # Set the initial size of the window

    self.data_filename = 'users_data.pkl'
    self.users_data = self.load_data()

    self.current_user = None

    self.show_sign_in_page()

  def load_data(self):
    try:
      with open(self.data_filename, 'rb') as file:
        if os.path.getsize(self.data_filename) > 0:
          return pickle.load(file)
        else:
          return []
    except (EOFError, FileNotFoundError):
      return []

  def save_data(self):
    with open(self.data_filename, 'wb') as file:
      pickle.dump(self.users_data, file)

  def show_sign_in_page(self):
    for widget in self.root.winfo_children():
      widget.destroy()

    sign_in_page = SignInPage(self.root, self)

  def get_user_by_username(self, username):
    for user in self.users_data:
      if user.email == username:
        return user
    return None

  def show_registration_type_page(self):
    for widget in self.root.winfo_children():
      widget.destroy()

    registration_type_page = RegistrationTypePage(self.root, self)

  def show_registration_page(self, role):
    for widget in self.root.winfo_children():
      widget.destroy()

    register_page = RegisterPage(self.root, self, role)

  def show_user_details_page(self, user):
    for widget in self.root.winfo_children():
      widget.destroy()

    user_details_page = UserDetailsPage(self.root, self, user)


class SignInPage:

  def __init__(self, root, app):
    self.root = root
    self.app = app
    self.max_attempts = 3 
    self.attempts = 0
    self.root.title("Sign In")

    self.label_username = tk.Label(root, text="Username (email):")
    self.label_username.pack(pady=5)

    self.entry_username = tk.Entry(root, width=30)
    self.entry_username.pack(pady=5)

    self.label_password = tk.Label(root, text="Password:")
    self.label_password.pack(pady=5)

    self.entry_password = tk.Entry(root, width=30, show="*")
    self.entry_password.pack(pady=5)

    self.show_password_var = tk.BooleanVar()
    self.checkbox_show_password = tk.Checkbutton(root, text="Show Password", variable=self.show_password_var,
                                                     command=self.toggle_password_visibility)
    self.checkbox_show_password.pack(pady=5)

    self.button_submit = tk.Button(root,
                                       text="Submit",
                                       command=self.verify_user)
    self.button_submit.pack()
    self.label_new_user = tk.Label(root, text="A new user? register here", fg="blue",font= ('Helvetica 10 underline'))
    self.label_new_user.pack(pady=10)

    self.label_new_user.bind("<Button-1>", self.show_registration_type_page)
  def toggle_password_visibility(self):
        show_password = self.show_password_var.get()
        if show_password:
            self.entry_password.config(show="")
        else:
            self.entry_password.config(show="*")
  def deactivate_account(self, user):
    self.app.users_data.remove(user)
    self.app.save_data()
    self.app.show_sign_in_page()

  def verify_user(self):
    username = self.entry_username.get()
    password = self.entry_password.get()

    # Verify if the username and password match a registered user
    user = self.app.get_user_by_username(username)

    if user and user.password == password:
      self.app.show_user_details_page(user)
    elif user:
            self.attempts += 1  # Increment the attempts counter

            if self.attempts >= self.max_attempts:
                messagebox.showerror("Error", "Maximum attempts reached. Account deactivated.")
                self.deactivate_account(user)

                self.attempts = 0
            else:
                remaining_attempts = self.max_attempts - self.attempts
                messagebox.showerror("Error", f"Wrong password. {remaining_attempts} attempts remaining.")
    else:
      messagebox.showerror("Error", "Invalid username.")

  def show_registration_type_page(self, event):
    self.app.show_registration_type_page()


class RegistrationTypePage:

  def __init__(self, root, app):
    self.root = root
    self.app = app

    self.root.title("Registration Type")

    self.label_registration_type = tk.Label(root,
                                            text="Select Registration Type:")
    self.label_registration_type.pack(pady=10)

    self.button_teacher = tk.Button(
        root,
        text="Teacher",
        command=lambda: self.show_registration_page("Teacher"))
    self.button_teacher.pack(pady=6)

    self.button_ug_student = tk.Button(
        root,
        text="UG Student",
        command=lambda: self.show_registration_page("UGStudent"))
    self.button_ug_student.pack(pady=6)

    self.button_pg_student = tk.Button(
        root,
        text="PG Student",
        command=lambda: self.show_registration_page("PGStudent"))
    self.button_pg_student.pack(pady=6)
    self.button_back = tk.Button(root,
                                     text="Back",
                                     command=self.go_back)
    self.button_back.pack(pady=5)

  def show_registration_page(self, role):
    self.app.show_registration_page(role)
  def go_back(self):
    self.app.show_sign_in_page()


class RegisterPage:

  def __init__(self, root, app, role):
    self.root = root
    self.app = app
    self.role = role

    self.root.title(f"Register {role}")
    self.label_role = tk.Label(root, text=f"Role : {role}")
    self.label_role.pack(pady=5)

    self.label_name = tk.Label(root, text="Name:")
    self.label_name.pack(pady=1)

    self.entry_name = tk.Entry(root, width=30)
    self.entry_name.pack(pady=1)

    self.label_email = tk.Label(root, text="Email:")
    self.label_email.pack(pady=1)

    self.entry_email = tk.Entry(root, width=30)
    self.entry_email.pack(pady=1)

    self.label_password = tk.Label(root, text="Password:")
    self.label_password.pack(pady=1)

    self.entry_password = tk.Entry(root, width=30, show="*")
    self.entry_password.pack(pady=1)
    self.show_password_var = tk.BooleanVar()
    self.checkbox_show_password = tk.Checkbutton(root, text="Show Password", variable=self.show_password_var,
                                                     command=self.toggle_password_visibility)
    self.checkbox_show_password.pack(pady=5)

    if role == "Teacher":
      self.label_subject = tk.Label(root, text="Subject:")
      self.label_subject.pack(pady=1)
      self.entry_subject = tk.Entry(root, width=30)
      self.entry_subject.pack(pady=1)
    elif role == "UGStudent":
      self.label_roll_number = tk.Label(root, text="Roll Number:")
      self.label_roll_number.pack(pady=1)
      self.entry_roll_number = tk.Entry(root, width=30)
      self.entry_roll_number.pack(pady=1)
      self.label_department = tk.Label(root, text="Department:")
      self.label_department.pack(pady=1)
      self.entry_department = tk.Entry(root, width=30)
      self.entry_department.pack(pady=1)
    elif role == "PGStudent":
      self.label_roll_number = tk.Label(root, text="Roll Number:")
      self.label_roll_number.pack(pady=1)
      self.entry_roll_number = tk.Entry(root, width=30)
      self.entry_roll_number.pack(pady=1)
      self.label_specialization = tk.Label(root, text="Specialization:")
      self.label_specialization.pack(pady=1)
      self.entry_specialization = tk.Entry(root, width=30)
      self.entry_specialization.pack(pady=1)

    self.button_register = tk.Button(root,
                                     text="Register",
                                     command=self.register_user)
    self.button_register.pack(pady=5)
    self.button_back = tk.Button(root,
                                     text="Back",
                                     command=self.go_back)
    self.button_back.pack(pady=5)

  def toggle_password_visibility(self):
        show_password = self.show_password_var.get()
        if show_password:
            self.entry_password.config(show="")
        else:
            self.entry_password.config(show="*")

  def go_back(self):
    self.app.show_registration_type_page()

  def register_user(self):
    name = self.entry_name.get()
    email = self.entry_email.get()
    password = self.entry_password.get()
    role = self.role

    # Validate input
    if not name or not email or not password:
      messagebox.showerror("Error", "Name, email, and password are required.")
      return

    # Validate email format
    if not re.match(r"[^@]+@[^@]+\.[^@]+", email):
      messagebox.showerror("Error", "Invalid email format.")
      return
    
    for user in self.app.users_data:
        if user.email == email:
            messagebox.showerror("Error", "User with the same email already exists.")
            return

    # Validate password
    if not (8 <= len(password) <= 12):
      messagebox.showerror("Error", "Password should be 8-12 characters long.")
      return

    if not any(char.isupper() for char in password):
      messagebox.showerror(
          "Error", "Password should contain at least one uppercase letter.")
      return

    if not any(char.islower() for char in password):
      messagebox.showerror(
          "Error", "Password should contain at least one lowercase letter.")
      return

    if not any(char.isdigit() for char in password):
      messagebox.showerror("Error",
                           "Password should contain at least one digit.")
      return

    if not any(char in "!@#$%&*" for char in password):
      messagebox.showerror(
          "Error",
          "Password should contain at least one special character from [!@#$%&*]."
      )
      return

    if ' ' in password:
      messagebox.showerror("Error",
                           "Password should not contain blank spaces.")
      return

    # Add user based on role
    if role == "Teacher":
      subject = self.entry_subject.get()
      if not subject:
        messagebox.showerror(
            "Error", "Subject is required for Teacher registration.")
        return
      new_user = Teacher(name, email, password, subject)
    elif role == "UGStudent":
      roll_number = self.entry_roll_number.get()
      department = self.entry_department.get()
      if not roll_number or not department:
        messagebox.showerror(
            "Error",
            "Roll Number and Department are required for UG Student registration.")
        return
      new_user = UGStudent(name, email, password, roll_number, department)
    elif role == "PGStudent":
      roll_number = self.entry_roll_number.get()
      specialization = self.entry_specialization.get()
      if not roll_number or not specialization:
        messagebox.showerror(
            "Error",
            "Roll Number and Specialization are required for PG Student registration.")
        return
      new_user = PGStudent(name, email, password,roll_number, specialization)
    else:
      messagebox.showerror("Error", "Invalid role.")
      return

    self.app.users_data.append(new_user)
    self.app.save_data()
    messagebox.showinfo("Success", "Registration successful!")
    self.app.show_user_details_page(new_user)


class UserDetailsPage:

  def __init__(self, root, app, user):
    self.root = root
    self.app = app
    self.user = user

    self.root.title("User Details")

    self.label_name = tk.Label(root, text="Name:")
    self.label_name.pack(pady=1)

    self.entry_name = tk.Entry(root, width=30)
    self.entry_name.pack(pady=1)

    self.label_email = tk.Label(root, text="Email:")
    self.label_email.pack(pady=1)

    self.entry_email = tk.Entry(root, width=30)
    self.entry_email.pack(pady=1)

    self.label_password = tk.Label(root, text="Password:")
    self.label_password.pack(pady=1)

    self.entry_password = tk.Entry(root, width=30, show="*")
    self.entry_password.pack(pady=1)

    self.show_password_var = tk.BooleanVar()
    self.checkbox_show_password = tk.Checkbutton(root, text="Show Password", variable=self.show_password_var,
                                                     command=self.toggle_password_visibility)
    self.checkbox_show_password.pack(pady=5)

    if isinstance(user, Teacher):
      self.label_subject = tk.Label(root, text="Subject:")
      self.entry_subject = tk.Entry(root, width=30)
      self.label_subject.pack(pady=1)
      self.entry_subject.pack(pady=1)
    elif isinstance(user, UGStudent):
      self.label_roll_number = tk.Label(root, text="Roll Number:")
      self.entry_roll_number = tk.Entry(root, width=30)
      self.label_roll_number.pack(pady=1)
      self.entry_roll_number.pack(pady=1)
      self.label_department = tk.Label(root, text="Department:")
      self.entry_department = tk.Entry(root, width=30)
      self.label_department.pack(pady=1)
      self.entry_department.pack(pady=1)
    elif isinstance(user, PGStudent):
      self.label_roll_number = tk.Label(root, text="Roll Number:")
      self.entry_roll_number = tk.Entry(root, width=30)
      self.label_roll_number.pack(pady=1)
      self.entry_roll_number.pack(pady=1)
      self.label_specialization = tk.Label(root, text="Specialization:")
      self.entry_specialization = tk.Entry(root, width=30)
      self.label_specialization.pack(pady=1)
      self.entry_specialization.pack(pady=1)

    self.button_save = tk.Button(root,
                                 text="Save",
                                 command=self.save_user_details)
    self.button_save.pack(pady=5)
    self.button_logout = tk.Button(root,
                                       text="Logout",
                                       command=self.logout)
    self.button_logout.pack(pady=5)

    self.button_deregister = tk.Button(root,
                                       text="Deregister",
                                       command=self.deregister_user)
    self.button_deregister.pack(pady=5)

    self.load_user_details()

  def toggle_password_visibility(self):
        show_password = self.show_password_var.get()
        if show_password:
            self.entry_password.config(show="")
        else:
            self.entry_password.config(show="*")

  def logout(self):
        confirmation = messagebox.askyesno("Confirmation", "Are you sure you want to logout?")
        if confirmation:
            self.app.show_sign_in_page()

  def load_user_details(self):
    self.entry_name.insert(0, self.user.name)
    self.entry_email.insert(0, self.user.email)
    self.entry_password.insert(0, self.user.password)

    if isinstance(self.user, Teacher):
      self.entry_subject.insert(0, self.user.subject)
    elif isinstance(self.user, UGStudent):
      self.entry_roll_number.insert(0, self.user.roll_number)
      self.entry_department.insert(0, self.user.department)
    elif isinstance(self.user, PGStudent):
      self.entry_roll_number.insert(0, self.user.roll_number)
      self.entry_specialization.insert(0, self.user.specialization)

  def save_user_details(self):
    name = self.entry_name.get()
    email = self.entry_email.get()
    password = self.entry_password.get()

    if not name or not email or not password:
      messagebox.showerror("Error", "Name, email, and password are required.")
      return

    if not re.match(r"[^@]+@[^@]+\.[^@]+", email):
      messagebox.showerror("Error", "Invalid email address.")
      return

    if not (8 <= len(password) <= 12):
      messagebox.showerror("Error", "Password should be 8-12 characters long.")
      return

    if not any(char.isupper() for char in password):
      messagebox.showerror(
          "Error", "Password should contain at least one uppercase letter.")
      return

    if not any(char.islower() for char in password):
      messagebox.showerror(
          "Error", "Password should contain at least one lowercase letter.")
      return

    if not any(char.isdigit() for char in password):
      messagebox.showerror("Error",
                           "Password should contain at least one digit.")
      return

    if not any(char in "!@#$%&*" for char in password):
      messagebox.showerror(
          "Error",
          "Password should contain at least one special character from [!@#$%&*]."
      )
      return

    if ' ' in password:
      messagebox.showerror("Error",
                           "Password should not contain blank spaces.")
      return
    if isinstance(self.user, Teacher):
            subject = self.entry_subject.get()
            if not subject:
                messagebox.showerror("Error", "Subject is required for Teacher.")
                return

    elif isinstance(self.user, UGStudent):
            roll_number = self.entry_roll_number.get()
            department = self.entry_department.get()
            if not roll_number or not department:
                messagebox.showerror("Error", "Roll Number and Department are required for UG Student.")
                return

    elif isinstance(self.user, PGStudent):
            roll_number = self.entry_roll_number.get()
            specialization = self.entry_specialization.get()
            if not roll_number or not specialization:
                messagebox.showerror("Error", "Roll Number and Specialization are required for UG Student.")
                return

    # Update user details
    self.user.name = name
    self.user.email = email
    self.user.password = password

    if isinstance(self.user, Teacher):
      self.user.subject = self.entry_subject.get()
    elif isinstance(self.user, UGStudent):
      self.user.roll_number = self.entry_roll_number.get()
      self.user.department = self.entry_department.get()
    elif isinstance(self.user, PGStudent):
      self.user.roll_number = self.entry_roll_number.get()
      self.user.specialization = self.entry_specialization.get()

    # Show confirmation message
    messagebox.showinfo("Success", "User details saved.")

    # Save the updated data to the pickle file
    self.app.save_data()

  def deregister_user(self):
    confirmation = messagebox.askyesno("Confirmation",
                                       "Are you sure you want to deregister?")
    if confirmation:
      self.app.users_data.remove(self.user)
      self.app.save_data()
      messagebox.showinfo("Success", "User deregistered.")
      self.app.show_sign_in_page()

root = tk.Tk()
app = MainClass(root)
root.mainloop()