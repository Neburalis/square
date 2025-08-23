#!/usr/bin/env python3
"""
Синхронизация определений функций в header файлах с их реализациями в cpp файлах.
"""

import os
import re
from pathlib import Path
from typing import Dict, List, Tuple, Optional, Set
import argparse


class FunctionSignature:
    """Представление сигнатуры функции."""
    
    def __init__(self, return_type: str, name: str, params: str, 
                 const: bool = False, noexcept: bool = False,
                 virtual: bool = False, static: bool = False,
                 inline: bool = False, override: bool = False):
        self.return_type = return_type.strip()
        self.name = name.strip()
        self.params = params.strip()
        self.const = const
        self.noexcept = noexcept
        self.virtual = virtual
        self.static = static
        self.inline = inline
        self.override = override
        
    def to_declaration(self) -> str:
        """Преобразование в объявление для header файла."""
        parts = []
        
        if self.virtual:
            parts.append("virtual")
        if self.static:
            parts.append("static")
        if self.inline:
            parts.append("inline")
            
        parts.append(self.return_type)
        parts.append(self.name)
        parts.append(f"({self.params})")
        
        if self.const:
            parts.append("const")
        if self.noexcept:
            parts.append("noexcept")
        if self.override:
            parts.append("override")
            
        return " ".join(parts) + ";"
    
    def __str__(self):
        return self.to_declaration()
    
    def normalize_params(self, params: str) -> str:
        """Нормализация параметров для сравнения."""
        # Убираем лишние пробелы
        params = re.sub(r'\s+', ' ', params.strip())
        # Убираем пробелы вокруг запятых
        params = re.sub(r'\s*,\s*', ',', params)
        # Убираем пробелы вокруг звездочек и амперсандов
        params = re.sub(r'\s*\*\s*', '*', params)
        params = re.sub(r'\s*&\s*', '&', params)
        return params
    
    def __eq__(self, other):
        if not isinstance(other, FunctionSignature):
            return False
        # Нормализуем параметры для сравнения
        self_params = self.normalize_params(self.params)
        other_params = self.normalize_params(other.params)
        return (self.name == other.name and 
                self_params == other_params and
                self.const == other.const)
    
    def __hash__(self):
        return hash((self.name, self.normalize_params(self.params), self.const))


class CppParser:
    """Парсер для C++ файлов."""
    
    # Регулярные выражения для поиска функций с телом
    FUNCTION_PATTERN = re.compile(
        r'''
        # Опциональные модификаторы
        (?:(?P<modifiers>(?:virtual|static|inline|explicit|constexpr)\s+)*)?
        # Возвращаемый тип (может включать template, namespace, указатели и ссылки, std::)
        (?P<return_type>(?:(?:std::)?[\w:]+(?:\s*[*&])?(?:\s*const)?|\w+))\s+
        # Имя функции (может включать namespace)
        (?P<name>(?:[\w]+::)*[\w]+)\s*
        # Параметры
        \((?P<params>[^)]*)\)\s*
        # Опциональные модификаторы после параметров
        (?P<post_modifiers>(?:\s*const)?(?:\s*noexcept)?(?:\s*override)?)?
        # Начало тела функции
        \s*\{
        ''',
        re.VERBOSE | re.MULTILINE | re.DOTALL
    )
    
    # Регулярное выражение для поиска объявлений функций (без тела)
    DECLARATION_PATTERN = re.compile(
        r'''
        ^[ \t]*  # Начало строки, возможные отступы
        # Опциональные модификаторы
        (?:(?P<modifiers>(?:virtual|static|inline|explicit|constexpr)\s+)*)?
        # Возвращаемый тип (может включать enum, template, namespace, указатели и ссылки, std::)
        (?P<return_type>(?:enum\s+)?(?:(?:std::)?[\w:]+(?:\s*[*&])?(?:\s*const)?|\w+))\s+
        # Имя функции (может включать namespace)
        (?P<name>(?:[\w]+::)*[\w]+)\s*
        # Параметры
        \((?P<params>[^)]*)\)\s*
        # Опциональные модификаторы после параметров
        (?P<post_modifiers>(?:\s*const)?(?:\s*noexcept)?(?:\s*override)?)?
        # Точка с запятой (объявление)
        \s*;
        ''',
        re.VERBOSE | re.MULTILINE
    )
    
    # Паттерн для поиска классов
    CLASS_PATTERN = re.compile(
        r'(?:class|struct)\s+(?P<name>\w+)(?:\s*:\s*(?:public|private|protected)\s+[\w:]+)?'
    )
    
    def __init__(self):
        self.current_class = None
        
    def parse_file(self, filepath: Path) -> Dict[str, List[FunctionSignature]]:
        """Парсинг C++ файла и извлечение функций."""
        with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
        
        # Удаляем комментарии
        content = self._remove_comments(content)
        
        # Находим все классы
        classes = {}
        for match in self.CLASS_PATTERN.finditer(content):
            class_name = match.group('name')
            classes[class_name] = []
        
        # Глобальные функции
        global_functions = []
        
        # Находим все функции
        for match in self.FUNCTION_PATTERN.finditer(content):
            modifiers = match.group('modifiers') or ''
            return_type = match.group('return_type')
            name = match.group('name')
            params = match.group('params')
            post_modifiers = match.group('post_modifiers') or ''
            
            # Пропускаем конструкторы и деструкторы в определениях
            if return_type == name or name.startswith('~'):
                continue
                
            # Пропускаем недопустимые конструкции (if, else, for, while и т.д.)
            if name in ['if', 'else', 'for', 'while', 'switch', 'case', 'default', 'return', 'break', 'continue']:
                continue
                
            # Пропускаем если имя содержит недопустимые символы для функций
            if not re.match(r'^[a-zA-Z_][a-zA-Z0-9_]*$', name):
                continue
                
            # Создаем сигнатуру функции
            sig = FunctionSignature(
                return_type=return_type,
                name=name,
                params=params,
                const='const' in post_modifiers,
                noexcept='noexcept' in post_modifiers,
                virtual='virtual' in modifiers,
                static='static' in modifiers,
                inline='inline' in modifiers,
                override='override' in post_modifiers
            )
            
            # Определяем к какому классу относится функция
            if '::' in name:
                class_name, func_name = name.rsplit('::', 1)
                sig.name = func_name
                if class_name in classes:
                    classes[class_name].append(sig)
            else:
                # Попробуем определить по контексту
                # Для упрощения добавляем в глобальные
                global_functions.append(sig)
        
        result = {'global': global_functions}
        result.update(classes)
        return result
    
    def _remove_comments(self, content: str) -> str:
        """Удаление комментариев из C++ кода."""
        # Удаляем однострочные комментарии
        content = re.sub(r'//.*?$', '', content, flags=re.MULTILINE)
        # Удаляем многострочные комментарии
        content = re.sub(r'/\*.*?\*/', '', content, flags=re.DOTALL)
        return content


class HeaderSynchronizer:
    """Синхронизатор header файлов."""
    
    def __init__(self):
        self.parser = CppParser()
        self.cpp_files = []
        self.header_files = []
        
    def scan_directory(self, directory: Path):
        """Сканирование директории на наличие C++ файлов."""
        for root, dirs, files in os.walk(directory):
            for file in files:
                filepath = Path(root) / file
                if file.endswith(('.cpp', '.cc', '.cxx', '.c++')):
                    self.cpp_files.append(filepath)
                elif file.endswith(('.h', '.hpp', '.hxx', '.h++')):
                    self.header_files.append(filepath)
    
    def find_corresponding_header(self, cpp_file: Path) -> Optional[Path]:
        """Поиск соответствующего header файла для cpp файла."""
        base_name = cpp_file.stem
        
        # Ищем header с таким же базовым именем
        for header in self.header_files:
            if header.stem == base_name:
                # Предпочитаем header в той же директории
                if header.parent == cpp_file.parent:
                    return header
        
        # Если не нашли в той же директории, ищем в других
        for header in self.header_files:
            if header.stem == base_name:
                return header
        
        return None
    
    def extract_header_declarations(self, header_file: Path) -> Set[FunctionSignature]:
        """Извлечение существующих объявлений из header файла."""
        with open(header_file, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
        
        # Удаляем комментарии
        content = self.parser._remove_comments(content)
        
        all_declarations = set()
        
        # Находим все объявления функций (с точкой с запятой)
        for match in self.parser.DECLARATION_PATTERN.finditer(content):
            modifiers = match.group('modifiers') or ''
            return_type = match.group('return_type')
            name = match.group('name')
            params = match.group('params')
            post_modifiers = match.group('post_modifiers') or ''
            
            # Пропускаем конструкторы и деструкторы
            if return_type == name or name.startswith('~'):
                continue
                
            # Пропускаем недопустимые конструкции (if, else, for, while и т.д.)
            if name in ['if', 'else', 'for', 'while', 'switch', 'case', 'default', 'return', 'break', 'continue']:
                continue
                
            # Пропускаем если имя содержит недопустимые символы для функций
            if not re.match(r'^[a-zA-Z_][a-zA-Z0-9_]*$', name):
                continue
            
            # Создаем сигнатуру функции
            sig = FunctionSignature(
                return_type=return_type,
                name=name,
                params=params,
                const='const' in post_modifiers,
                noexcept='noexcept' in post_modifiers,
                virtual='virtual' in modifiers,
                static='static' in modifiers,
                inline='inline' in modifiers,
                override='override' in post_modifiers
            )
            
            all_declarations.add(sig)
        
        return all_declarations
    
    def find_functions_to_update(self, existing_declarations: Set[FunctionSignature], 
                                cpp_functions: Set[FunctionSignature]) -> Tuple[Set[FunctionSignature], Dict[FunctionSignature, FunctionSignature]]:
        """Находит функции для добавления и обновления."""
        new_functions = set()
        functions_to_update = {}
        
        # Создаем словарь существующих функций по имени для быстрого поиска
        existing_by_name = {}
        for func in existing_declarations:
            existing_by_name[func.name] = func
        
        for cpp_func in cpp_functions:
            if cpp_func.name in existing_by_name:
                existing_func = existing_by_name[cpp_func.name]
                # Если функция существует, но отличается - помечаем для обновления
                if existing_func != cpp_func:
                    functions_to_update[existing_func] = cpp_func
            else:
                # Если функции нет - добавляем как новую
                new_functions.add(cpp_func)
        
        return new_functions, functions_to_update

    def update_header(self, header_file: Path, cpp_functions: Dict[str, List[FunctionSignature]]):
        """Обновление header файла с новыми объявлениями и обновление существующих."""
        with open(header_file, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
        
        # Получаем существующие объявления
        existing_declarations = self.extract_header_declarations(header_file)
        
        # Собираем все функции из cpp
        all_cpp_functions = set()
        for class_name, funcs in cpp_functions.items():
            for func in funcs:
                all_cpp_functions.add(func)
        
        # Находим функции для добавления и обновления
        new_functions, functions_to_update = self.find_functions_to_update(existing_declarations, all_cpp_functions)
        
        if not new_functions and not functions_to_update:
            print(f"  Header {header_file.name} уже синхронизирован")
            return False
        
        changes_made = False
        lines = content.split('\n')
        
        # Обновляем существующие объявления
        if functions_to_update:
            print(f"  Обновляем {len(functions_to_update)} объявлений в {header_file.name}")
            changes_made = True
            
            for old_func, new_func in functions_to_update.items():
                old_declaration = old_func.to_declaration()
                new_declaration = new_func.to_declaration()
                
                # Ищем и заменяем старое объявление
                for i, line in enumerate(lines):
                    line_stripped = line.strip()
                    # Проверяем совпадение имени функции в строке
                    if (old_func.name in line_stripped and 
                        line_stripped.endswith(';') and
                        '(' in line_stripped and ')' in line_stripped):
                        
                        # Дополнительная проверка - это действительно объявление функции
                        if re.search(rf'\b{re.escape(old_func.name)}\s*\(', line_stripped):
                            # Сохраняем исходные отступы
                            indent = line[:-len(line.lstrip())]
                            lines[i] = indent + new_declaration
                            print(f"    Обновлено: {old_func.name}")
                            break
        
        # Добавляем новые функции
        if new_functions:
            print(f"  Добавляем {len(new_functions)} новых объявлений в {header_file.name}")
            changes_made = True
            
            # Ищем #endif для вставки перед ним
            insert_pos = len(lines)
            for i in range(len(lines) - 1, -1, -1):
                if lines[i].strip().startswith('#endif'):
                    insert_pos = i
                    break
            
            # Добавляем новые объявления
            new_declarations = []
            if not any("// Автоматически синхронизированные объявления" in line for line in lines):
                new_declarations.append("\n// Автоматически синхронизированные объявления")
            for func in new_functions:
                new_declarations.append(func.to_declaration())
            new_declarations.append("")
            
            lines[insert_pos:insert_pos] = new_declarations
        
        if changes_made:
            # Записываем обновленный header
            with open(header_file, 'w', encoding='utf-8') as f:
                f.write('\n'.join(lines))
        
        return changes_made
    
    def synchronize(self, directory: Path, dry_run: bool = False):
        """Главный метод синхронизации."""
        print(f"Сканирование директории: {directory}")
        self.scan_directory(directory)
        
        print(f"Найдено {len(self.cpp_files)} cpp файлов и {len(self.header_files)} header файлов\n")
        
        updated_count = 0
        
        for cpp_file in self.cpp_files:
            print(f"Обработка {cpp_file.name}...")
            
            # Находим соответствующий header
            header_file = self.find_corresponding_header(cpp_file)
            if not header_file:
                print(f"  Не найден соответствующий header файл")
                continue
            
            print(f"  Найден header: {header_file.name}")
            
            # Парсим cpp файл
            cpp_functions = self.parser.parse_file(cpp_file)
            
            # Подсчитываем функции
            total_functions = sum(len(funcs) for funcs in cpp_functions.values())
            if total_functions == 0:
                print(f"  Не найдено функций для синхронизации")
                continue
            
            print(f"  Найдено {total_functions} функций в cpp файле")
            
            if dry_run:
                print(f"  [DRY RUN] Будет обновлен {header_file.name}")
            else:
                # Обновляем header
                if self.update_header(header_file, cpp_functions):
                    updated_count += 1
            
            print()
        
        print(f"\nСинхронизация завершена. Обновлено header файлов: {updated_count}")


def main():
    parser = argparse.ArgumentParser(
        description='Синхронизация определений функций в header файлах с cpp файлами'
    )
    parser.add_argument(
        'directory',
        nargs='?',
        default='.',
        help='Директория для сканирования (по умолчанию: текущая)'
    )
    parser.add_argument(
        '--dry-run',
        action='store_true',
        help='Показать что будет изменено без внесения изменений'
    )
    
    args = parser.parse_args()
    
    directory = Path(args.directory).resolve()
    if not directory.is_dir():
        print(f"Ошибка: {directory} не является директорией")
        return 1
    
    synchronizer = HeaderSynchronizer()
    synchronizer.synchronize(directory, dry_run=args.dry_run)
    
    return 0


if __name__ == '__main__':
    exit(main())