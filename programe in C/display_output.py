import subprocess
import tkinter as tk
from tkinter import ttk, font

def run_c_program(c_program_path, args=None):
    """Run the C program and capture its output."""
    command = [c_program_path]
    if args:
        command.extend(args)
    
    try:
        result = subprocess.run(command, check=True, text=True, capture_output=True)
        return result.stdout.strip()
    except subprocess.CalledProcessError as e:
        return f"Error running C program: {e}\nError output: {e.stderr}"
    except FileNotFoundError:
        return f"C program not found at: {c_program_path}"

def display_output_window(output):
    """Display the output in a new window."""
    # Create the main window
    root = tk.Tk()
    root.title("C Program Output")
    root.geometry("600x400")
    
    # Configure the window style
    style = ttk.Style()
    style.theme_use("clam")  # Use a modern theme
    
    # Create a frame to hold the content
    main_frame = ttk.Frame(root, padding="20")
    main_frame.pack(fill=tk.BOTH, expand=True)
    
    # Display the header
    header_font = font.Font(family="Arial", size=14, weight="bold")
    header = ttk.Label(main_frame, text="Program Output", font=header_font)
    header.pack(pady=(0, 15))
    
    # Display the output in a text widget
    output_font = font.Font(family="Consolas", size=12)
    output_text = tk.Text(main_frame, font=output_font, wrap=tk.WORD, height=10)
    output_text.insert(tk.END, output)
    output_text.config(state=tk.DISABLED)  # Make it read-only
    
    # Add scrollbars
    scrollbar = ttk.Scrollbar(main_frame, command=output_text.yview)
    output_text.config(yscrollcommand=scrollbar.set)
    
    # Pack the text widget and scrollbar
    output_text.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
    scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
    
    # Add a close button
    button_frame = ttk.Frame(root, padding="10")
    button_frame.pack(fill=tk.X)
    close_button = ttk.Button(button_frame, text="Close", command=root.destroy)
    close_button.pack(side=tk.RIGHT)
    
    # Start the main loop
    root.mainloop()

def main():
    # Path to your C program executable
    c_program_path = "./computor"
    
    # Get any arguments from the command line
    print("Enter arguments for the C program (or press Enter if none):")
    args_input = input().strip()
    args = args_input.split() if args_input else None
    
    # Run the C program and get its output
    output = run_c_program(c_program_path, args)
    
    # Display the output in a new window
    display_output_window(output)

if __name__ == "__main__":
    main()