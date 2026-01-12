// csv-parse - CSV parsing benchmark
// Tests string processing, field extraction, quote handling
// Self-contained with embedded test data

#[derive(Default, Debug)]
struct ParseStats {
    row_count: usize,
    field_count: usize,
    quoted_field_count: usize,
    total_chars: usize,
}

/// Parse a single CSV field starting at position, returns (field, end_pos, is_quoted)
fn parse_field(line: &[u8], start: usize) -> (String, usize, bool) {
    let mut pos = start;
    let mut field = String::new();
    let mut is_quoted = false;

    // Skip leading whitespace
    while pos < line.len() && (line[pos] == b' ' || line[pos] == b'\t') {
        pos += 1;
    }

    if pos < line.len() && line[pos] == b'"' {
        // Quoted field
        is_quoted = true;
        pos += 1;
        while pos < line.len() {
            if line[pos] == b'"' {
                if pos + 1 < line.len() && line[pos + 1] == b'"' {
                    // Escaped quote
                    field.push('"');
                    pos += 2;
                } else {
                    // End of quoted field
                    pos += 1;
                    break;
                }
            } else {
                field.push(line[pos] as char);
                pos += 1;
            }
        }
    } else {
        // Unquoted field
        while pos < line.len() && line[pos] != b',' && line[pos] != b'\n' {
            field.push(line[pos] as char);
            pos += 1;
        }
    }

    // Skip to next field or end
    while pos < line.len() && (line[pos] == b' ' || line[pos] == b'\t') {
        pos += 1;
    }
    if pos < line.len() && line[pos] == b',' {
        pos += 1;
    }

    (field, pos, is_quoted)
}

/// Parse a CSV line, update stats
fn parse_line(line: &[u8], stats: &mut ParseStats) -> usize {
    if line.is_empty() || line[0] == b'\n' {
        return 0;
    }

    let mut pos = 0;
    let mut fields = 0;

    while pos < line.len() && line[pos] != b'\n' {
        let (field, new_pos, is_quoted) = parse_field(line, pos);
        pos = new_pos;
        fields += 1;
        stats.total_chars += field.len();
        if is_quoted {
            stats.quoted_field_count += 1;
        }
    }

    stats.field_count += fields;
    stats.row_count += 1;
    fields
}

/// Parse entire CSV data
fn parse_csv(data: &[u8], stats: &mut ParseStats) {
    *stats = ParseStats::default();

    for line in data.split(|&b| b == b'\n') {
        if !line.is_empty() {
            parse_line(line, stats);
        }
    }
}

// Test data - various CSV scenarios
const TEST_DATA: &[u8] = b"name,age,city,salary
John Doe,30,New York,50000
Jane Smith,25,Los Angeles,60000
\"Bob \"\"The Builder\"\" Jones\",45,Chicago,75000
Alice,28,\"San Francisco, CA\",80000
Charlie Brown,35,Boston,55000
\"Diana, Princess\",40,London,90000
Edward,22,Miami,45000
\"Fiona \"\"Fi\"\" Green\",33,Seattle,70000
George,29,Denver,52000
Helen,31,Phoenix,58000";

// Row template for large dataset
const LARGE_DATA_ROW: &[u8] = b"field1,field2,field3,field4,field5,\"quoted,field\",field7,field8,field9,field10\n";

fn generate_large_dataset(rows: usize) -> Vec<u8> {
    let mut data = Vec::with_capacity(rows * LARGE_DATA_ROW.len());
    for _ in 0..rows {
        data.extend_from_slice(LARGE_DATA_ROW);
    }
    data
}

fn main() {
    println!("CSV Parse Benchmark");

    // Parse test data
    let mut stats = ParseStats::default();
    parse_csv(TEST_DATA, &mut stats);

    println!("Small dataset:");
    println!("  Rows: {}", stats.row_count);
    println!("  Fields: {}", stats.field_count);
    println!("  Quoted fields: {}", stats.quoted_field_count);
    println!("  Total chars: {}", stats.total_chars);
    println!();

    // Generate and parse larger dataset
    let large_data = generate_large_dataset(1000);
    parse_csv(&large_data, &mut stats);

    println!("Large dataset (1000 rows):");
    println!("  Rows: {}", stats.row_count);
    println!("  Fields: {}", stats.field_count);
    println!("  Quoted fields: {}", stats.quoted_field_count);
    println!("  Total chars: {}", stats.total_chars);

    println!("\nDone.");
}
