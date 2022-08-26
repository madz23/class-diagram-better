///
/// \Authors Hunter, Patience
/// \file ClassParser.hh
/// \note A class parser that uses static methods to take in a string, parse the string for classes, methods, and fields
///       and return what is parsed as a vector of ClassInfo objects filled with Method and Field objects.
///

#pragma once

#include <string>
#include <vector>
#include <set>
#include <regex>
#include "ClassInfo.hh"
#include "Method.hh"
#include "Field.hh"
#include "Type.hh"

/// <summary>
/// Used to parse a given string for any classes and the data associated with that class (methods, fields, types, scopes, etc.)
/// </summary>
class ClassParser {
private:
    // Static Fields
    static std::regex classRegex;
    static std::regex methodRegex;
    static std::regex fieldRegex;
    static std::regex scopeRegex;
    static std::regex typeRegex;
    static std::regex commentRegex;
    static std::regex inheritanceRegex;

    static std::set<std::string> collectionTypes;

public:

    /// <summary>
    /// Parses a the given string for classes and their methods and fields and returns a vector of all the classes found.
    /// </summary>
    /// <param name="classContents">The string to parse for classes</param>
    /// <returns>A vector of ClassInfo objects filled with the methods and fields found in the string for that class</returns>
    static std::vector<ClassInfo> parseClasses(std::string classContents) {
        std::vector<ClassInfo> classInfos;
        std::smatch classMatch;
        unsigned int startPosition = 0;
        unsigned int endPosition = 0;

        classContents = removeComments(classContents);

        // Find all the classes in the given piece of text
        while (std::regex_search(classContents, classMatch, classRegex)) {
            // Get the contents of the class that was matched and get the strings for it
            std::tie(startPosition, endPosition) = findMatchingMarks(classContents.substr(classMatch.position()));
            std::string classSection = classContents.substr(classMatch.position() + startPosition, endPosition - startPosition + 1);

            // Create the class that was found
            ClassInfo classInfo(classMatch[1]);
            
            // Get the inheritances from the class match
            parseInheritance(classMatch[2], classInfo);

            // Breaks the class sections into public, private, and protected sections and passes
            // them into the parse methods and fields methods
            std::vector<std::tuple<std::string, std::string>> scopeSections = findScopeSections(classSection);

            for (const auto &scopeSection: scopeSections) {
                // Break out the scope and the text associated
                std::string scope;
                std::string scopeContents;
                std::tie(scope, scopeContents) = scopeSection;

                // Gather the methods in the scope section of the class and add them to the class object
                std::string nonMethodScopeContents = parseMethods(scopeContents, classInfo, scope);
                parseFields(nonMethodScopeContents, classInfo, scope);
            }

            // Add the class to the vector of classes
            classInfos.push_back(classInfo);

            classContents = classMatch.suffix().str();
        }
        return classInfos;
    }

private:

    // Static Helper Methods

    /// <summary>
    /// Removes any comments from the given string contents.
    /// </summary>
    /// <param name="contents">The text to remove comments from</param>
    /// <returns>The input string with any comments removed</returns>
    static std::string removeComments(std::string contents) {
        std::smatch commentMatch;
        std::string nonCommentContents = "";

        while (std::regex_search(contents, commentMatch, commentRegex)) {
            nonCommentContents.append(contents.substr(0, commentMatch.position()));
            contents = commentMatch.suffix().str();
        }
        nonCommentContents.append(contents);
        return nonCommentContents;
    }

    /// <summary>
    /// Parses the given string for any methods and adds them to the given class object with the given scope.
    /// </summary>
    /// <param name="sectionContents">The string to parse for methods</param>
    /// <param name="classInfo">The class object to put the parsed methods into</param>
    /// <param name="scope">The scope of the methods</param>
    /// <returns>The string contents not associated with the methods that are matched in the sectionContents. Everything not a method header or the body of a method.</returns>
    static std::string parseMethods(std::string sectionContents, ClassInfo &classInfo, const std::string &scope) {
        std::smatch methodMatch;
        std::string nonMethodContents = "";

        
        while (std::regex_search(sectionContents, methodMatch, methodRegex)) {
            nonMethodContents.append(sectionContents.substr(0, methodMatch.position()));
            classInfo.addMethod(Method(methodMatch[2], parseType(methodMatch[1]), scope, methodMatch[3]));
            sectionContents = methodMatch.suffix().str();


            // If the method has a body (opening and closing curly braces)...
            int i = 0;
            while (sectionContents[i] == ' ' || sectionContents[i] == '\n') {
                i++;
            }

            // find the body section and remove it from the search string
            if (sectionContents[i] == '{') {
                int closingMarkIndex;
                std::tie(std::ignore, closingMarkIndex) = findMatchingMarks(sectionContents);
                sectionContents = sectionContents.substr(closingMarkIndex, sectionContents.length() - closingMarkIndex + 1);
            }
        }
        nonMethodContents.append(sectionContents);
        return nonMethodContents;
    }

    /// <summary>
    /// Parses the given string for any fields and adds them to the given class object with the given scope.
    /// </summary>
    /// <param name="sectionContents">The string to parse for fields</param>
    /// <param name="classInfo">The class object to put the parsed fields into</param>
    /// <param name="scope">The scope of the fields</param>
    static void parseFields(std::string sectionContents, ClassInfo &classInfo, const std::string &scope) {
        // TODO: Actually figure out how to do this. (remove methods from string?)
        //std::cout << sectionContents << std::endl << std::endl;
        std::smatch fieldMatch;
        while (std::regex_search(sectionContents, fieldMatch, fieldRegex)) {
            classInfo.addField(Field(fieldMatch[2], parseType(fieldMatch[1]), scope));
            sectionContents = fieldMatch.suffix().str();
        }
    }

    /// <summary>
    /// Parses the given string for a method or field type and several features about the type
    /// </summary>
    /// <param name="typeContents">The text to parse for type data</param>
    /// <returns>a Type object containing the data parsed from the input text</returns>
    static Type parseType(std::string typeContents) {
        std::smatch typeMatch;
        std::regex_search(typeContents, typeMatch, typeRegex);
        // Matches:
        // 0 -> The whole match
        // 1 -> The namespace if there is one
        // 2 -> The actual object type (may be a collection)
        // 3 -> The contents of the <> if there is one
        // 4 -> The actual type of the contents of the <>
        Type type;
        if (collectionTypes.count(typeMatch[2])) {
            type = Type(typeMatch[4], typeMatch[1], typeMatch[2]);
        } else {
            type = Type(typeMatch[2], typeMatch[1]);
        }
        return type;
    }
    
    static void parseInheritance(std::string sectionContents, ClassInfo &classInfo) {
        std::smatch inheritanceMatch;
        while (std::regex_search(sectionContents, inheritanceMatch, inheritanceRegex)) {
            classInfo.addBase(inheritanceMatch[1]);
            sectionContents = inheritanceMatch.suffix().str();
        }
    }

    /// <summary>
    /// Finds the indices for matching opening and closing marks in a string of text based on what marks are specified.
    /// </summary>
    /// <param name="text">The text to search for the matching opening and closing marks</param>
    /// <param name="markOffset">The number of matching marks to skip</param>
    /// <param name="openMark">The character to use as the opening mark to find (e.g. '(', '{', '[', '<')</param>
    /// <param name="closeMark">The character to use as the closing mark to find (e.g. ')', '}', ']', '>')</param>
    /// <returns>a tuple containing the indices for the corresponding opening and closing marks respectively</returns>
    static std::tuple<int, int> findMatchingMarks(const std::string &text, int markOffset = 0, char openMark = '{', char closeMark = '}') {
        // Start at -1 so that the first increment of openPosition starts with the 0th character
        int openPosition = -1;
        int closePosition = 0;

        // This allows us to skip a number of matching braces equal to the markOffset
        int count = -markOffset;

        // Get the textLength ahead of time to reduce length calls
        long long textLength = text.length();

        // Find the position of the desired opening mark
        while (count < 1 && openPosition < textLength) {
            openPosition++;
            if (text[openPosition] == openMark) count++;
        }

        // Now that we have the open mark position, start from there and find the closing mark position
        closePosition = openPosition;
        while (count > 0 && closePosition < textLength) {
            closePosition++;
            if (text[closePosition] == closeMark) count--;
            else if (text[closePosition] == openMark) count++;
        }

        // If either the closing mark or opening mark are not found withing the bounds of the text, set the position to
        // -1 to symbolize non-existence
        if (closePosition >= textLength) return std::make_tuple(-1, -1);
        return std::make_tuple(openPosition, closePosition);
    }

    /// <summary>
    /// Finds a breaks up scope sections for a given string
    /// </summary>
    /// <param name="text">The string to break up into scope sections</param>
    /// <returns>a vector of tuples where the first index of the tuple is the scope and the second is the code section</returns>
    static std::vector<std::tuple<std::string, std::string>> findScopeSections(const std::string &text) {
        std::vector<std::tuple<std::string, std::string>> scopeSections;
        std::smatch scopeMatch;
        std::string textCopy = text;

        // Initial variables for grabbing the first section of anything not in a specifier
        unsigned long long previousIndex = 0;
        unsigned long long indexOffset = 0;

        // No specifier defaults to private
        std::string scope = "private";

        // Regex for 'public:', 'private:', and 'protected:' and add the previous section to the scopeSections
        while (std::regex_search(textCopy, scopeMatch, scopeRegex)) {
            // Calculate the current index relative to the original text file
            unsigned long long currentIndex = scopeMatch.position() + indexOffset;

            // Add the substring that occurs from the start index of the previous match to 1 minus the index of the
            // current match
            scopeSections.emplace_back(scope, text.substr(previousIndex, currentIndex - previousIndex));

            // The scope matched in this loop iteration is the scope that will be added in the next loop iteration
            scope = scopeMatch[1];

            // Calculate the previous index relative to the original text file
            previousIndex = currentIndex;

            // Update the search string so the regex doesn't match the same thing over and over again
            textCopy = scopeMatch.suffix().str();

            // Have to calculate an indexOffset since each subsequent regex search trims the string; thus match
            // positions are no longer relative to the original string
            indexOffset = text.length() - textCopy.length() - 1;
        }
        scopeSections.emplace_back(scope, text.substr(previousIndex, text.length() - previousIndex));

        return scopeSections;
    }
};
