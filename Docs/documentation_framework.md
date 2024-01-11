# A-Life Challenge Documentation Framework

## Introduction
Documentation is a vital part of the software development process. A well-documented project is more reliable, reusable, and scalable. To that end, this document outlines the framework for documentation in the A-Life Challenge Capstone Project. In short, there are two kinds of documentation that will be written: descriptive documentation, which describes in separate files the components, interactions, and usage of the program and the project, and source documentation, which explains the code directly in the source files.

## Descriptive Documentation
Descriptive documentation should generally be written in Markdown (.md) files and stored in /docs/. These documents should have a unique name (within the scope of the folder) in uncapitalized snake case (e.g., document_name.md).

### Architecture and Process Documents
Some documents in /docs/ may describe the program architecture or the development process (such as this document). Text descriptions should be written in Markdown files, but image and diagram files are permissable too. Generally, images or diagrams should be accompanied by a text file providing context, interpretation, justification, or description.

### Source and Header Files
In general, each pair of .cpp and .hpp files in /src/ should have one Markdown document describing their contents. The Markdown documents should be named exactly the same as their corresponding .cpp or .hpp files, except for the extension (e.g., cell.md should be the Markdown file name for cell.cpp and cell.hpp). The structure and content of these documents should adhere to the template provided in /docs/src_file_description_template.md.

Pull requests containing changes to or the addition of /src/ files should include updates to or the creation of corresponding Markdown description files. For example, if a new method is added to cell.cpp and cell.hpp, cell.md should be updated to reflect the changes.

### Usage Instructions
Some documents may provide instructions (technical or non-technical) for the usage of the program, its components, or the tools used in development. Documents intended to be published to the user may be written in Word (.docx) format and stored in /docs/. These document should be exported as PDFs, which may also be stored in /docs/.

## Source Documentation
Source code should be documented concisely in comments throughout. These comments should primarily describe in plain English the purpose and function of the next several lines of code. They may also provide clarifications, warnings, and organizational markings. It is not necessary to list parameters, pre- and post-conditions, etc. within the code since this information should be listed in the corresponding Markdown file in /docs/.
