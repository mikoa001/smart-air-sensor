# Contributing to Smart Air Quality Sensor

Thank you for your interest in contributing! This document provides guidelines for contributing to the project.

## How to Contribute

### Reporting Issues

If you find a bug or have a feature request:

1. **Check existing issues** to avoid duplicates
2. **Create a new issue** with a clear title and description
3. **Include details**:
   - Hardware components used
   - Software version
   - Serial output/error messages
   - Steps to reproduce (for bugs)
   - Expected vs actual behavior

### Submitting Changes

1. **Fork the repository**
2. **Create a feature branch** (`git checkout -b feature/amazing-feature`)
3. **Make your changes**
4. **Test thoroughly** on actual hardware if possible
5. **Commit your changes** (`git commit -m 'Add amazing feature'`)
6. **Push to your fork** (`git push origin feature/amazing-feature`)
7. **Create a Pull Request**

## Development Guidelines

### Code Style

- Follow existing code formatting
- Use meaningful variable names
- Add comments for complex logic
- Keep functions focused and concise

#### Example:
```cpp
// Good
float readTemperature() {
  float temp = dht.readTemperature();
  return isnan(temp) ? 0.0 : temp;
}

// Avoid
float rt() {
  return dht.readTemperature();
}
```

### Configuration

- Never commit `src/config.h` with credentials
- Update `config.h.example` if adding new settings
- Document all configuration options

### Documentation

- Update README.md for major features
- Add to CHANGELOG.md
- Update relevant .md files (HARDWARE.md, WIRING.md, etc.)
- Include comments in code for complex features

### Testing

Before submitting:
- [ ] Code compiles without errors
- [ ] Test on actual hardware if possible
- [ ] Verify WiFi connection works
- [ ] Check MQTT publishing
- [ ] Verify sensor readings
- [ ] Test LED display
- [ ] Check serial output for errors

### Commit Messages

Use clear, descriptive commit messages:

```
Good:
- "Add support for SCD41 sensor"
- "Fix MQTT reconnection issue"
- "Update documentation for LED matrix wiring"

Avoid:
- "Update"
- "Fix bug"
- "Changes"
```

## Areas for Contribution

### High Priority
- Testing on different ESP8266 boards
- Home Assistant integration examples
- Alternative sensor support
- Power optimization
- Error handling improvements

### Documentation
- Translation to other languages
- Video tutorials
- Assembly photos
- Enclosure designs (3D printable)

### Features
- Web configuration interface
- OTA updates
- Data logging
- Alternative displays
- Additional sensors

### Testing
- Different hardware combinations
- Edge case scenarios
- Long-term stability
- Power consumption measurements

## Pull Request Guidelines

### PR Checklist
- [ ] Code follows project style
- [ ] Documentation updated
- [ ] CHANGELOG.md updated
- [ ] Tested on hardware (if applicable)
- [ ] No credentials committed
- [ ] Branch is up to date with main

### PR Description
Include:
- What the PR does
- Why the change is needed
- Testing performed
- Any breaking changes
- Related issues (use #issue_number)

Example:
```markdown
## Description
Adds support for SCD41 CO2 sensor as alternative to SCD40.

## Motivation
SCD41 offers better accuracy and is becoming more common.

## Testing
- Tested on NodeMCU with SCD41
- Verified readings match expected values
- MQTT publishing works correctly

## Breaking Changes
None - backwards compatible with SCD40

Closes #42
```

## Code of Conduct

### Our Standards
- Be respectful and inclusive
- Welcome newcomers
- Focus on constructive feedback
- Collaborate openly

### Unacceptable Behavior
- Harassment or discrimination
- Trolling or insulting comments
- Publishing others' private information
- Other unprofessional conduct

## Questions?

- Open an issue for general questions
- Tag with "question" label
- Check existing discussions

## License

By contributing, you agree that your contributions will be licensed under the same license as the project (MIT License).

## Recognition

Contributors will be recognized in:
- README.md (Contributors section)
- Release notes
- CHANGELOG.md (where applicable)

Thank you for contributing! 🎉
